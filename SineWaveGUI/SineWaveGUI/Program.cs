using System;
using System.Drawing;
using System.Text;
using System.IO.Ports;
//using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using CyUSB;

namespace SineWaveGUI
{

    static class Program
    {


        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }

    class WaveFormGenUSBComm
    {
        private static USBDeviceList USBDevices;
        private static CyUSBDevice USBDevice;
        private static MainForm displayForm;
        private static CyBulkEndPoint InEP;
        private static CyBulkEndPoint OutEP;
        private readonly object CommLock = new object();

        public WaveFormGenUSBComm(MainForm form)
        {
            displayForm = form;
            
           
            GetUSBDevice();
            USBDevices.DeviceAttached += new EventHandler(USBAdded);
            USBDevices.DeviceRemoved += new EventHandler(USBRemoved);

        }

        public void GetUSBDevice()
        {
            USBDevices = new USBDeviceList(CyConst.DEVICES_MSC | CyConst.DEVICES_CYUSB);
            USBDevice = USBDevices[0x04B4, 0xF232] as CyUSBDevice; // looking for my device only



            if (USBDevice != null)
            {
                displayForm.USBStatusLabel = USBDevice.FriendlyName + " connected.";
                InEP = USBDevice.BulkInEndPt;
                InEP.TimeOut = 1000;
                OutEP = USBDevice.BulkOutEndPt;
                OutEP.TimeOut = 1000;
            }
            else
            {
                displayForm.USBStatusLabel = "Not Connected.";
                InEP = null;
                OutEP = null;
            }

        }

       void USBRemoved(object sender, EventArgs e)
        {
            displayForm.WaveFormGenRunning = false;
            USBEventArgs USBevent = (USBEventArgs)e;
            displayForm.USBStatusLabel = "Not Connected.";
        }
        void USBAdded(object sender, EventArgs e)
        {
            USBEventArgs USBevent = (USBEventArgs)e;
            GetUSBDevice();
            displayForm.USBStatusLabel = USBevent.FriendlyName + " Connected.";
        }

        public void StartWaveForm()
        {
            lock (CommLock)
                    {
                int len = 64;
                byte[] cmd = new byte[len];
                cmd = Encoding.ASCII.GetBytes("SA");
                byte[] ret = new byte[len];


                if (OutEP.XferData(ref cmd, ref len))
                {
                    if (InEP.XferData(ref ret, ref len))
                    {
                        string Result = System.Text.Encoding.UTF8.GetString(ret);
                        Result = Result.Substring(0, 2);
                        if (Result == "OK")
                        {
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                    }

                    return;
                }
                else
                {
                    //display error
                }
            }

        }

        public void StopWaveForm()
        {
            lock (CommLock)
            { 
                int len = 64;
            byte[] cmd = new byte[len];
            cmd = Encoding.ASCII.GetBytes("STP");
            byte[] ret = new byte[len];
            if (OutEP.XferData(ref cmd, ref len))
            {
                if (InEP.XferData(ref ret, ref len))
                {
                    string Result = System.Text.Encoding.UTF8.GetString(ret);
                    Result = Result.Substring(0, 2);
                    if (Result == "OK")
                    {
                    }
                    else
                    {
                    }
                }
                else
                { 
                }
                    return;
            }
            else
            {
                //display error
            }
            }
        }

        public double ReadVoltage()
        {
            lock (CommLock)
            {
                int len = 64;
                byte[] cmd = new byte[len];
                cmd = Encoding.ASCII.GetBytes("RV");
                byte[] ret = new byte[len];
                if (OutEP.XferData(ref cmd, ref len))
                {
                    if (InEP.XferData(ref ret, ref len))
                    {
                        string Result = System.Text.Encoding.UTF8.GetString(ret);
                        int EndOfString = Result.IndexOf('\0');
                        Result = Result.Substring(0, EndOfString);
                        if (Result == "NG" || Result == "OK")
                        {
                            return 0;
                        }
                        else
                        {
                            double i = double.Parse(Result);
                            i = i / 1000;
                            return i;
                        }
                    }
                    else
                    {
                    }
                    return 0;
                }
                else
                {
                    //display error
                    return 0;
                }
            }
        }

        public void ReadVoltage(ref TextBox T)
        {
            lock (CommLock)
            {
                int len = 64;
                byte[] cmd = new byte[len];
                cmd = Encoding.ASCII.GetBytes("RV");
                byte[] ret = new byte[len];
                if (OutEP.XferData(ref cmd, ref len))
                {
                    if (InEP.XferData(ref ret, ref len))
                    {
                        string Result = System.Text.Encoding.UTF8.GetString(ret);
                        int EndOfString = Result.IndexOf('\0');
                        Result = Result.Substring(0, EndOfString);
                        if (Result == "NG")
                        {
                        }
                        else
                        {
                            decimal i = decimal.Parse(Result);
                            i = i / 1000;
                            T.Text = i.ToString("0.000");
                        }
                    }
                    else
                    {
                    }
                    return;
                }
                else
                {
                    //display error
                }
            }

        }
        public void WriteFreq(int freq, ref TextBox T)
        {
            lock (CommLock)
            {
                if (freq <= 10 && freq >= 1)
                {
                    int len = 64;
                    byte[] cmd = new byte[len];
                    string f = freq.ToString("00");
                    cmd = Encoding.ASCII.GetBytes("F" + f);

                    byte[] ret = new byte[len];
                    if (OutEP.XferData(ref cmd, ref len))
                    {
                        if (InEP.XferData(ref ret, ref len))
                        {
                            string Result = System.Text.Encoding.UTF8.GetString(ret);
                            int EndOfString = Result.IndexOf('\0');
                            Result = Result.Substring(0, EndOfString);
                            if (Result == "NG")
                            {
                                T.BackColor = Color.DarkRed;
                            }
                            else
                            {
                                T.BackColor = Color.White;
                            }
                        }
                        else
                        {
                        }
                        return;
                    }
                    else
                    {
                        //display error
                    }

                }
            }
        }

    }
}


        




    

