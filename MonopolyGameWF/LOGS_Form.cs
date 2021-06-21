using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MonopolyGameWF
{
    public partial class LOGS_Form : Form
    {
        private Point mouseOffset;
        private bool isMouseDown = false;

        public LOGS_Form()
        {
            InitializeComponent();
        }
        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape) this.Close();
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            int xOffset;
            int yOffset;

            if (e.Button == MouseButtons.Left)
            {
                xOffset = -e.X - SystemInformation.FrameBorderSize.Width;
                yOffset = -e.Y - SystemInformation.CaptionHeight -
                    SystemInformation.FrameBorderSize.Height;
                mouseOffset = new Point(xOffset, yOffset);
                isMouseDown = true;
            }
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            if (isMouseDown)
            {
                Point mousePos = Control.MousePosition;
                mousePos.Offset(mouseOffset.X, mouseOffset.Y);
                Location = mousePos;
            }
        }

        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                isMouseDown = false;
            }
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            if (richTextBox1.Text.Length > (richTextBox1.MaxLength * 0.9))
            {
                string[] lines = richTextBox1.Lines;
                richTextBox1.Text = lines[0];
                for (int i = (int)(lines.Length * 0.7); i < lines.Length; i++) richTextBox1.Text += lines[i];
            }
        }

        public void addLine(string[] temp)
        {
            string[] lines = new string[richTextBox1.Lines.Length+temp.Length];

            string[] buffer = richTextBox1.Lines;
            if (!string.IsNullOrEmpty(richTextBox1.Text))
            {
                richTextBox1.Text = buffer[0] + "\n";
            }

            for (int i = 0; i < temp.Length; i++)
            {
                richTextBox1.Text += $"{temp[i]}";
                if (temp.Length > 1) richTextBox1.Text += "\n";
            }
            for (int i = 1; i < buffer.Length; i++) richTextBox1.Text += $"\n{buffer[i]}";
        }
    }
}
