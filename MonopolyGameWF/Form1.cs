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
    public partial class Form1 : Form
    {
        Button[] buttons = new Button[24];
        Button[] figures = new Button[4];
        Button toMove;
        int whoIsMoving = 0;
        int timeControl = 0;
        
        public Form1()
        {
            buttonsCreate();

            for (int i = 0; i < 24; i++) Controls.Add(buttons[i]);
            for (int i = 0; i < 4; i++) Controls.Add(figures[i]);
            Controls.Add(toMove);

            figures[0].BringToFront();
            figures[1].BringToFront();
            figures[2].BringToFront();
            figures[3].BringToFront();

            InitializeComponent();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (whoIsMoving == 4) whoIsMoving = 0;

            figures[whoIsMoving].Location = new Point(figures[whoIsMoving].Location.X+10, figures[whoIsMoving].Location.Y);
            timeControl++;

            if (timeControl == 10)
            {
                timer1.Stop();
                timeControl = 0;
                toMove.Enabled = true;
                whoIsMoving++;
            }
        }

        private void toMove_Click(object sender, EventArgs e)
        {
            timer1.Start();
            toMove.Enabled = false;
        }

        //==============================================================
        private void buttonsCreate()
        {
            for (int i = 0; i < 24; i++)
            {
                buttons[i] = new Button();
                buttons[i].Enabled = true;
                buttons[i].Visible = true;
                buttons[i].Size = new Size(100, 100);
                buttons[i].Text = i.ToString();
            }

            for (int i = 0; i < 8; i++)
            {
                buttons[i].Location = new Point(i * 100, 0);
            }
            buttons[8].Location = new Point(700, 100);
            buttons[9].Location = new Point(700, 200);
            buttons[10].Location = new Point(700, 300);
            buttons[11].Location = new Point(700, 400);
            buttons[12].Location = new Point(0, 100);
            buttons[13].Location = new Point(0, 200);
            buttons[14].Location = new Point(0, 300);
            buttons[15].Location = new Point(0, 400);
            for (int i = 0; i < 8; i++)
            {
                buttons[i + 16].Location = new Point(i * 100, 500);
            }

            //====== ФИГУРКИ ======
            for (int i = 0; i < 4; i++) figures[i] = new Button();
            foreach (Button figure in figures)
            {
                figure.Size = new Size(50,50);
                figure.Text = " ";
                figure.Visible = true;
                figure.Enabled = false;
                figure.FlatStyle = FlatStyle.Flat;
                figure.BackgroundImageLayout = ImageLayout.Stretch;
            }

            // =========кортинки======
            figures[0].BackgroundImage = Properties.Resources.comboburst_1 ;
            figures[1].BackgroundImage = Properties.Resources.comboburst_11 ;
            figures[2].BackgroundImage = Properties.Resources.comboburst_13 ;
            figures[3].BackgroundImage = Properties.Resources.comboburst_9 ;

            //=========место==========
            figures[0].Location = new Point(0, 0);
            figures[1].Location = new Point(50, 0);
            figures[2].Location = new Point(0, 50);
            figures[3].Location = new Point(50, 50);

            // =======ДВИЖЕНИЯ КНОПКА========
            toMove = new Button();
            toMove.Size = new Size(80,30);
            toMove.Text = "жми бабай";
            toMove.Enabled = true;
            toMove.Visible = true;
            toMove.Click += toMove_Click;
            toMove.Location = new Point(180, 120);
        }
    }
}
