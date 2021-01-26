using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MonopolyGameWF
{
    class Figure
    {
        public Button b;
        public int direction;

        public Figure(int id)
        {
            direction = 0;

            b = new Button();
            b.Size = new Size(50, 50);
            b.Text = " ";
            b.Visible = true;
            b.Enabled = false;
            b.FlatStyle = FlatStyle.Flat;
            b.BackgroundImageLayout = ImageLayout.Stretch;

            configure(id);
        }

        public void checkForDir()
        {

        }

        private void configure(int id)
        {
            switch (id)
            {
                case 0:
                    b.BackgroundImage = Properties.Resources.comboburst_1;
                    b.Location = new Point(0, 0);
                    break;
                case 1:
                    b.BackgroundImage = Properties.Resources.comboburst_11;
                    b.Location = new Point(50, 0);
                    break;
                case 2:
                    b.BackgroundImage = Properties.Resources.comboburst_13;
                    b.Location = new Point(0, 50);
                    break;
                case 3:
                    b.BackgroundImage = Properties.Resources.comboburst_9;
                    b.Location = new Point(50, 50);
                    break;
            }
        }
    }
}
