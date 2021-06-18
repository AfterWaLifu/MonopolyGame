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
    public partial class Form2 : Form
    {
        public int quantity;
        public Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            quantity = (int)numericUpDown1.Value;
            MessageBox.Show("А цель этой игры стать самым богатым, в данном случае - 15000 денех и ты победитель",
                "Немного правил");
            this.Close();
        }
    }
}
