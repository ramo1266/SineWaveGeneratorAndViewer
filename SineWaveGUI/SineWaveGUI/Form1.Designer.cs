
namespace SineWaveGUI
{
    partial class MainForm  
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.StartWaveForm_button = new System.Windows.Forms.Button();
            this.StopWaveForm_Button = new System.Windows.Forms.Button();
            this.Waveform_Chart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.WaveFormFreq_TextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.USBConnectedStatus_label = new System.Windows.Forms.Label();
            this.Connect_button = new System.Windows.Forms.Button();
            this.ReadVoltage_button = new System.Windows.Forms.Button();
            this.VoltageReading_textBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Waveform_Chart)).BeginInit();
            this.SuspendLayout();
            // 
            // StartWaveForm_button
            // 
            this.StartWaveForm_button.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StartWaveForm_button.Location = new System.Drawing.Point(41, 30);
            this.StartWaveForm_button.Name = "StartWaveForm_button";
            this.StartWaveForm_button.Size = new System.Drawing.Size(185, 63);
            this.StartWaveForm_button.TabIndex = 0;
            this.StartWaveForm_button.Text = "Start";
            this.StartWaveForm_button.UseVisualStyleBackColor = true;
            this.StartWaveForm_button.Click += new System.EventHandler(this.StartWaveForm_button_Click);
            // 
            // StopWaveForm_Button
            // 
            this.StopWaveForm_Button.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StopWaveForm_Button.Location = new System.Drawing.Point(41, 120);
            this.StopWaveForm_Button.Name = "StopWaveForm_Button";
            this.StopWaveForm_Button.Size = new System.Drawing.Size(185, 63);
            this.StopWaveForm_Button.TabIndex = 1;
            this.StopWaveForm_Button.Text = "Stop";
            this.StopWaveForm_Button.UseVisualStyleBackColor = true;
            this.StopWaveForm_Button.Click += new System.EventHandler(this.StopWaveForm_Button_Click);
            // 
            // Waveform_Chart
            // 
            chartArea1.Name = "ChartArea1";
            this.Waveform_Chart.ChartAreas.Add(chartArea1);
            this.Waveform_Chart.Location = new System.Drawing.Point(12, 230);
            this.Waveform_Chart.Name = "Waveform_Chart";
            series1.ChartArea = "ChartArea1";
            series1.Name = "Series1";
            this.Waveform_Chart.Series.Add(series1);
            this.Waveform_Chart.Size = new System.Drawing.Size(776, 208);
            this.Waveform_Chart.TabIndex = 2;
            this.Waveform_Chart.Text = "chart1";
            // 
            // WaveFormFreq_TextBox
            // 
            this.WaveFormFreq_TextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.WaveFormFreq_TextBox.Location = new System.Drawing.Point(583, 53);
            this.WaveFormFreq_TextBox.Name = "WaveFormFreq_TextBox";
            this.WaveFormFreq_TextBox.Size = new System.Drawing.Size(146, 40);
            this.WaveFormFreq_TextBox.TabIndex = 3;
            this.WaveFormFreq_TextBox.TextChanged += new System.EventHandler(this.WaveFormFreq_TextBox_TextChanged);
            this.WaveFormFreq_TextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.WaveFormFreq_TextBox_KeyDown);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(579, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(188, 20);
            this.label1.TabIndex = 4;
            this.label1.Text = "WaveForm Frequency:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(735, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(31, 20);
            this.label2.TabIndex = 5;
            this.label2.Text = "Hz";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(12, 483);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(145, 20);
            this.label3.TabIndex = 6;
            this.label3.Text = "Connection Status:";
            // 
            // USBConnectedStatus_label
            // 
            this.USBConnectedStatus_label.AutoSize = true;
            this.USBConnectedStatus_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.USBConnectedStatus_label.Location = new System.Drawing.Point(163, 483);
            this.USBConnectedStatus_label.Name = "USBConnectedStatus_label";
            this.USBConnectedStatus_label.Size = new System.Drawing.Size(116, 20);
            this.USBConnectedStatus_label.TabIndex = 7;
            this.USBConnectedStatus_label.Text = "Not Connected";
            // 
            // Connect_button
            // 
            this.Connect_button.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Connect_button.Location = new System.Drawing.Point(603, 469);
            this.Connect_button.Name = "Connect_button";
            this.Connect_button.Size = new System.Drawing.Size(185, 63);
            this.Connect_button.TabIndex = 8;
            this.Connect_button.Text = "Connect";
            this.Connect_button.UseVisualStyleBackColor = true;
            this.Connect_button.Visible = false;
            this.Connect_button.Click += new System.EventHandler(this.Connect_button_Click);
            // 
            // ReadVoltage_button
            // 
            this.ReadVoltage_button.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReadVoltage_button.Location = new System.Drawing.Point(335, 143);
            this.ReadVoltage_button.Name = "ReadVoltage_button";
            this.ReadVoltage_button.Size = new System.Drawing.Size(185, 40);
            this.ReadVoltage_button.TabIndex = 9;
            this.ReadVoltage_button.Text = "Read Voltage";
            this.ReadVoltage_button.UseVisualStyleBackColor = true;
            this.ReadVoltage_button.Visible = false;
            this.ReadVoltage_button.Click += new System.EventHandler(this.ReadVoltage_button_Click);
            // 
            // VoltageReading_textBox
            // 
            this.VoltageReading_textBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.VoltageReading_textBox.Location = new System.Drawing.Point(583, 143);
            this.VoltageReading_textBox.Name = "VoltageReading_textBox";
            this.VoltageReading_textBox.Size = new System.Drawing.Size(146, 40);
            this.VoltageReading_textBox.TabIndex = 10;
            this.VoltageReading_textBox.Visible = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(579, 111);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(148, 20);
            this.label4.TabIndex = 11;
            this.label4.Text = "Voltage Reading:";
            this.label4.Visible = false;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(735, 157);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 20);
            this.label5.TabIndex = 12;
            this.label5.Text = "Volt";
            this.label5.Visible = false;
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.Location = new System.Drawing.Point(335, 53);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(185, 40);
            this.button1.TabIndex = 13;
            this.button1.Text = "Set Freq";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Visible = false;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 544);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.VoltageReading_textBox);
            this.Controls.Add(this.ReadVoltage_button);
            this.Controls.Add(this.Connect_button);
            this.Controls.Add(this.USBConnectedStatus_label);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.WaveFormFreq_TextBox);
            this.Controls.Add(this.Waveform_Chart);
            this.Controls.Add(this.StopWaveForm_Button);
            this.Controls.Add(this.StartWaveForm_button);
            this.Name = "MainForm";
            this.Text = "Cypress Cntrl GUI";
            ((System.ComponentModel.ISupportInitialize)(this.Waveform_Chart)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button StartWaveForm_button;
        private System.Windows.Forms.Button StopWaveForm_Button;
        private System.Windows.Forms.DataVisualization.Charting.Chart Waveform_Chart;
        private System.Windows.Forms.TextBox WaveFormFreq_TextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label USBConnectedStatus_label;
        private System.Windows.Forms.Button Connect_button;
        private System.Windows.Forms.Button ReadVoltage_button;
        private System.Windows.Forms.TextBox VoltageReading_textBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button button1;
    }
}

