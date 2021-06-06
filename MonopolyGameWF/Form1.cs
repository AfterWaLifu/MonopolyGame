﻿using System;
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
        Figure[] figures = new Figure[4];
        Button[] infoButtons = new Button[4];
        Button toMove;
        int whoIsMoving = 0;
        int timeControl = 0;
        int diceResult = 0;
        int playersCount;

        public Form1()
        {
            playersCount = 4;
            buttonsCreate();

            for (int i = 0; i < playersCount; i++) figures[i] = new Figure(i);

            for (int i = 0; i < 24; i++) Controls.Add(buttons[i]);
            for (int i = 0; i < playersCount; i++) {
                Controls.Add(figures[i].b);
                Controls.Add(infoButtons[i]);
            }
            Controls.Add(toMove);

            figures[0].b.BringToFront();
            figures[1].b.BringToFront();
            figures[2].b.BringToFront();
            figures[3].b.BringToFront();

            InitializeComponent();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (whoIsMoving == playersCount) whoIsMoving = 0;

            hugeToMoveMethod();
            timeControl++;

            if (timeControl == 20*diceResult)
            {
                timer1.Stop();
                timeControl = 0;
                toMove.Enabled = true;
                whoIsMoving++;
            }

            label2.Text = $"Ходит: {whoIsMoving+1}";
        }

        private void toMove_Click(object sender, EventArgs e)
        {
            Random r = new Random();
            diceResult = r.Next(1,7);
            label1.Text = $"Результат броска: {diceResult}";
            timer1.Start();
            toMove.Enabled = false;
        }

        //================ ИНИЦИАЛИЗАЦИЯ КНОПОК ================================
        private void buttonsCreate()
        {
            // ======= кнопки места ========
            for (int i = 0; i < 24; i++)
            {
                buttons[i] = new Button();
                buttons[i].Enabled = true;
                buttons[i].Visible = true;
                buttons[i].Size = new Size(100, 100);
                buttons[i].Text = " ";
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

            // =========ИНФО КНОПКИ=========
            for (int i = 0; i < playersCount; i++)
            {
                Button b = new Button();
                b.Enabled = false;
                b.Visible = true;
                b.Size = new Size(100,40);
                b.Location = new Point(500+(i/2*100),155+(i%2*40));
                b.Text = i.ToString();
                infoButtons[i] = b;
            }

            // =======ДВИЖЕНИЯ КНОПКА========
            toMove = new Button();
            toMove.Size = new Size(120,60);
            toMove.Font = new Font(toMove.Font.Name, 14, toMove.Font.Style, toMove.Font.Unit);
            toMove.Text = "БРОСИТЬ КУБИК";
            toMove.Enabled = true;
            toMove.Visible = true;
            toMove.Click += toMove_Click;
            toMove.Location = new Point(160, 120);
        }

        private void hugeToMoveMethod()
        {
            figures[whoIsMoving].checkForDir();

            switch (figures[whoIsMoving].direction)
            {
                case 0:
                    figures[whoIsMoving].b.Location = new Point(figures[whoIsMoving].b.Location.X+5, figures[whoIsMoving].b.Location.Y);
                    break;
                case 1:
                    figures[whoIsMoving].b.Location = new Point(figures[whoIsMoving].b.Location.X, figures[whoIsMoving].b.Location.Y+5);
                    break;
                case 2:
                    figures[whoIsMoving].b.Location = new Point(figures[whoIsMoving].b.Location.X - 5, figures[whoIsMoving].b.Location.Y);
                    break;
                case 3:
                    figures[whoIsMoving].b.Location = new Point(figures[whoIsMoving].b.Location.X, figures[whoIsMoving].b.Location.Y-5);
                    break;
            }
        }
    }
}
