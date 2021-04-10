using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports; //arduino communication

namespace HMI
{
    public partial class Form1 : Form
    {
        bool connected = false;
        String[] ports;
        SerialPort port;
        public Form1()
        {
            InitializeComponent();
            disableControls();
            getPorts();
            foreach (String p in ports) {
                comboBox1.Items.Add(p);
                Console.WriteLine(p);
                if (ports[0]!= null)
                {
                    comboBox1.SelectedItem = ports[0];
                }
            }

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void getPorts()
        {
            ports = SerialPort.GetPortNames();
        }

        private void disableControls()
        {

        }
        private void connectArduino()
        {
            connected = true;
            string selected = comboBox1.SelectedItem.ToString();
            port = new SerialPort(selected, 9600, Parity.None, 8, StopBits.One);
            port.Open();
            port.Write("#Inicia\n");
            button2.Text = "disconnect";
            enableControls();
        }

        

        private void enableControls()
        {
            checkBox1.Enabled = true;
                
        }

        private void disconnectArduino()
        {
            connected = false;
            port.Write("#Para\n");
            port.Close();
            button2.Text = "Connect";
            disableControls();
        }


        private void button2_Click(object sender, EventArgs e)
        {
            if (!connected)
            {
                connectArduino();
            }
            else
            {
                disconnectArduino();
            }




        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (!connected)
                return;
            if (checkBox1.Checked)
            {
                port.Write("#LED1ON");

            }
            else
            {
                port.Write("#LED1OF");
            }
        }
    }
}
