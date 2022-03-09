using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.Threading;
using System.Diagnostics;

namespace SineWaveGUI
{
    public partial class MainForm : Form
    {
        public delegate void AddToWaveFormChart();
        public delegate void ClearWaveFormChart();
        public AddToWaveFormChart AddWaveFormDelegate;
        public ClearWaveFormChart ClearWaveFormDelegate;

        private WaveFormGenUSBComm USBcntrl;
        private Series Waveform_Series;
        private Stopwatch stopwatch;
        public bool WaveFormGenRunning;
        public MainForm()
        {
            InitializeComponent();
            USBcntrl = new WaveFormGenUSBComm(this);
             CheckForIllegalCrossThreadCalls = false;
            Waveform_Chart.Series.Clear();
            Waveform_Series = Waveform_Chart.Series.Add("WaveForm");
            Waveform_Series.ChartType = SeriesChartType.Spline;

                  WaveFormGenRunning = false;

            AddWaveFormDelegate = new AddToWaveFormChart(AddPointToWaveFormChart);
            ClearWaveFormDelegate = new ClearWaveFormChart(ClearWaveformChart);
         stopwatch = new Stopwatch();
            Thread WaveFormChartTrd = new Thread(new ThreadStart(ChartingWaveForm));
            WaveFormChartTrd.IsBackground = true;
            WaveFormChartTrd.Start();
            
        }

        public void AddPointToWaveFormChart()
        {
          
       Waveform_Series.Points.AddXY(stopwatch.ElapsedMilliseconds, USBcntrl.ReadVoltage());
           Waveform_Chart.ChartAreas[0].AxisX.Maximum = (stopwatch.ElapsedMilliseconds);
            Waveform_Chart.ChartAreas[0].AxisX.Minimum = stopwatch.ElapsedMilliseconds - 1000; //(stopwatch.ElapsedMilliseconds / 1000) - 1;

        }

        public void ClearWaveformChart()
        {
            Waveform_Chart.Series.Clear();
            Waveform_Series.Points.Clear();
            Waveform_Series = Waveform_Chart.Series.Add("WaveForm");
            Waveform_Series.ChartType = SeriesChartType.Spline;

        }

        private void ChartingWaveForm()
        {
            bool FirstRunAfterStop = true;
            stopwatch.Start();

            while (true)
            {
                Thread.Sleep(10);
                if (WaveFormGenRunning)
                {
                    if (Waveform_Chart.InvokeRequired && FirstRunAfterStop)
                    {
                        Waveform_Chart.Invoke(ClearWaveFormDelegate);
                    }

                    FirstRunAfterStop = false;

                    if (Waveform_Chart.InvokeRequired)
                    {
                        Waveform_Chart.Invoke(AddWaveFormDelegate);
                    }

                   


                    //  Waveform_Series.Points.AddXY(stopwatch.ElapsedMilliseconds, USBcntrl.ReadVoltage());
                }
                else
                {

                    // Waveform_Chart.Series.Clear();
                    FirstRunAfterStop = true;
                    stopwatch.Restart();
                }
            }
        }
         public string USBStatusLabel
        {
            set { USBConnectedStatus_label.Text = value; }
            get { return USBConnectedStatus_label.Text; }
        }

        public string VoltReadingTextBox
        {
            set { VoltageReading_textBox.Text = value; }
            get { return VoltageReading_textBox.Text; }
        }

        public String WaveFormFreqTextBox
        {
            set { WaveFormFreq_TextBox.Text = value; }
            get { return WaveFormFreq_TextBox.Text; }
        }
      
        private void Connect_button_Click(object sender, EventArgs e)
        {
            USBcntrl.GetUSBDevice();
        }

        private void StartWaveForm_button_Click(object sender, EventArgs e)
        {
            USBcntrl.StartWaveForm();
            WaveFormGenRunning = true;
        }

        private void StopWaveForm_Button_Click(object sender, EventArgs e)
        {
            USBcntrl.StopWaveForm();
            WaveFormGenRunning = false;
        }

        private void ReadVoltage_button_Click(object sender, EventArgs e)
        {
            USBcntrl.ReadVoltage(ref VoltageReading_textBox);
        }

       private void WaveFormFreq_TextBox_TextChanged(object sender, EventArgs e)
        {
            if (sender.GetType() == typeof(TextBox))
            {
                TextBox T = (TextBox)sender;
                int freq;
                int.TryParse(T.Text, out freq);
                if (freq >= 1 && freq <= 10)
                {
                    T.BackColor = Color.Green;
                  
                }
                else
                {
                    T.BackColor = Color.Red;
                }


            }
        }



        private void WaveFormFreq_TextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.GetType() == typeof(KeyEventArgs))
            {
                TextBox T = (TextBox)sender;
                KeyEventArgs K = (KeyEventArgs)e;
                if (K.KeyCode == Keys.Enter && T.BackColor == Color.Green)
                {
                    USBcntrl.WriteFreq(int.Parse(T.Text),ref T);
                }
            }
        }
    }
}
