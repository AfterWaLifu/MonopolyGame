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
        Figure[] figures;
        Button[] infoButtons;
        Button toMove;
        Button[] buyButtons = new Button[2];
        int whoIsMoving = 0;
        int lastMoved = 1;
        int timeControl = 0;
        int diceResult = 0;
        int playersCount;

        public Form1()
        {
            Form2 f = new Form2();
            f.ShowDialog();
            playersCount = f.quantity;
            figures = new Figure[playersCount];
            infoButtons = new Button[playersCount];

            for (int i = 0; i < playersCount; i++) figures[i] = new Figure(i);

            buttonsCreate();

            for (int i = 0; i < 24; i++) Controls.Add(buttons[i]);
            for (int i = 0; i < playersCount; i++) {
                Controls.Add(figures[i].b);
                Controls.Add(infoButtons[i]);
            }
            Controls.Add(toMove);
            Controls.Add(buyButtons[0]);
            Controls.Add(buyButtons[1]);

            for (int i = 0; i < playersCount; i++)
            {
                figures[i].b.BringToFront();
            }

            InitializeComponent();
            label4.Location = new Point(516, buyButtons[0].Location.Y + 28);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            hugeToMoveMethod();
            timeControl++;

            if (timeControl == 20*diceResult)
            {
                timer1.Stop();
                timeControl = 0;
                toMove.Enabled = true;
                buyButtons[0].Enabled = true;
                buyButtons[1].Enabled = true;
                whoIsMoving++;

                if (whoIsMoving == playersCount) whoIsMoving = 0;
                lastMoved = whoIsMoving;
                if (lastMoved == 0) lastMoved = figures.Length;

                label2.Text = $"Ходит: {whoIsMoving + 1}";
                label4.Text = $"Покупает: {lastMoved}";
            }
            infoButtons[whoIsMoving].Text = "Игрок " + (whoIsMoving + 1).ToString() + ": " + figures[whoIsMoving].money;
        }

        private void toMove_Click(object sender, EventArgs e)
        {
            Random r = new Random();
            diceResult = r.Next(1,7);
            label1.Text = $"Результат броска: {diceResult}";
            toMove.Enabled = false;
            buyButtons[0].Enabled = false;
            buyButtons[1].Enabled = false;
            figures[whoIsMoving].position += diceResult;
            if (figures[whoIsMoving].position > 23) figures[whoIsMoving].position -= 24;
            switch (figures[whoIsMoving].position)
            {
                case 4:
                case 8:
                case 12:
                case 16:
                case 20:
                    int num = numberFinder(figures[whoIsMoving].position);
                    MessageBox.Show($"Ваш бросок был на {diceResult}, но вы наступили на +{num} шагов");
                    diceResult += num;
                    figures[whoIsMoving].position += num;
                    if (figures[whoIsMoving].position > 23) figures[whoIsMoving].position -= 24;
                    break;
                default:
                    break;
            }
            timer1.Start();
        }
        private void checkButton_Click(object sender, EventArgs e)
        {
            string text = sender.ToString().Substring(sender.ToString().IndexOf(':')+2);
            MessageBox.Show(text, "А здесь у нас:");
        }

        //===== ИНИЦИАЛИЗАЦИЯ КНОПОК =====
        private void buttonsCreate()
        {
            // ======= кнопки места ========
            for (int i = 0; i < 24; i++)
            {
                buttons[i] = new Button();
                buttons[i].Enabled = true;
                buttons[i].Visible = true;
                buttons[i].Size = new Size(100, 100);
                buttons[i].Text = i.ToString();
                buttons[i].Click += checkButton_Click;
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

            buttonsNamer();

            // =========ИНФО КНОПКИ=========
            for (int i = 0; i < playersCount; i++)
            {
                Button b = new Button();
                b.Enabled = false;
                b.Visible = true;
                b.Size = new Size(120,30);
                b.Location = new Point(460+(i%2*120+1),155+(i/2*30+1));
                b.Font = new Font(b.Font.Name, 10, b.Font.Style, b.Font.Unit);
                b.FlatStyle = FlatStyle.Flat;
                b.BackColor = Color.White;
                b.Text = "Игрок "+(i+1).ToString() + ": " + figures[i].money;
                infoButtons[i] = b;
            }

            //========КУПЛЕПРОДАЖНЫЕ========
            for (int i = 0; i < 2; i++)
            {
                Button b = new Button();
                b.Enabled = true;
                b.Visible = true;
                b.Size = new Size(120, 30);
                b.Location = new Point(461+120*i, infoButtons[infoButtons.Length-1].Location.Y+30);
                b.Font = new Font(b.Font.Name, 10, b.Font.Style, b.Font.Unit);
                b.FlatStyle = FlatStyle.Flat;
                b.BackColor = Color.FromArgb(233, 120, 127);
                buyButtons[i] = b;
            }
            buyButtons[0].Click += buyButton_Click;
            buyButtons[1].Click += sellButton_Click;
            buyButtons[0].Text = "КУПИТЬ";
            buyButtons[1].Text = "ПРОДАТЬ";

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

        private void buttonsNamer()
        {
            buttons[0].Text = "Старт";
            buttons[1].Text = "Ларёк перед школой =50 +20";
            buttons[2].Text = "Ларёк с шаурмой =65 +30";
            buttons[3].Text = "Ларёк в центре =85 +40";
            buttons[4].Text = "Шаг вперёд";
            buttons[5].Text = "Завод палок =90 +30";
            buttons[6].Text = "Завод камней =100 +40";
            buttons[7].Text = "Завод каменных палок =110 +50";
            buttons[8].Text = "Два шага вперёд";
            buttons[9].Text = "Автомаркет Самара =220 +100";
            buttons[10].Text = "Автомаркет Волксваген =250 +120";
            buttons[11].Text = "Автомаркет Кухонда =300 +155";
            buttons[12].Text = "SpaceY ГенДир =1600 +800";
            buttons[13].Text = "SpaceY инженер =1400 +650";
            buttons[14].Text = "SpaceY уборщик =1000 +400";
            buttons[15].Text = "Четыре шага вперёд";
            buttons[16].Text = "Инвестор завода =500 +200";
            buttons[17].Text = "Инвестор DogeCoin =750 +350";
            buttons[18].Text = "Инвестор GameStop =950 +520";
            buttons[19].Text = "Пять вперёд";
            buttons[20].Text = "Военный =290 +130";
            buttons[21].Text = "Кибер полицейский =260 +125";
            buttons[22].Text = "Следователь =250 +110";
            buttons[23].Text = "Три шага вперёд";
        }

        private void hugeToMoveMethod()
        {
            figures[whoIsMoving].checkForDir();

            if (figures[whoIsMoving].WIN)
            {
                timer1.Stop();
                MessageBox.Show($"А ПОБЕДИЛ ИГРОК НОМЕР {whoIsMoving}","А ПОБЕДИЛ");
                Environment.Exit(0);
            }

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

        private int numberFinder(int num)
        {
            switch (figures[whoIsMoving].position)
            {
                case 4:
                    return 1;
                case 8:
                    return 2;
                case 12:
                    return 3;
                case 16:
                    return 5;
                case 20:
                    return 4;
                default:
                    return 0;
            };
        }

        // ======= КНОПКИ БОЛИ которые я очень не хочу делать ========

        private void buyButton_Click(object sender, EventArgs e)
        {
            string needed = buttons[figures[lastMoved - 1].position].Text;
            int cost = Convert.ToInt32(needed.Substring(needed.LastIndexOf("=") + 1, needed.LastIndexOf("+") - needed.LastIndexOf("=") - 1));
            int owner = whoIsTheOwner(figures[lastMoved-1].position);

            if (lookForThroughBuidings(figures[lastMoved-1], figures[lastMoved-1].position))
            {
                MessageBox.Show($"Игрок №{lastMoved} уже купил {needed}", "Ахтунг!");
            }
            else if (figures[lastMoved - 1].money < cost)
            {
                MessageBox.Show($"У игрока №{lastMoved} недосточно денег на {needed}", "Ахтунг!");
            }
            else if (owner < 5)
            {
                MessageBox.Show($"Предприятие '{needed}' уже под контролем игрока {owner}", "Ахтунг!");
            }
            else
            {
                int earn = Convert.ToInt32(needed.Substring(needed.LastIndexOf("+") + 1));
                figures[lastMoved - 1].buildings.Add(figures[lastMoved - 1].position);
                figures[lastMoved - 1].money -= cost;
                figures[lastMoved - 1].toEarn += earn;
                infoButtons[whoIsMoving].Text = "Игрок " + lastMoved.ToString() + ": " + figures[lastMoved-1].money;
            }
        }
        private void sellButton_Click(object sender, EventArgs e)
        {

        }

        private bool lookForThroughBuidings(Figure f, int building)
        {
            if (f.buildings.Count == 0) return false;
            for (int i = 0; i < f.buildings.Count;i++)
            {
                if (f.buildings[i] == building) return true;
            }
            return false;
        }
        private int whoIsTheOwner(int building)
        {
            for (int i = 0; i < figures.Length; i++)
            {
                if (figures[i].buildings.Count == 0) continue;
                for (int j = 0; j < figures[i].buildings.Count; j++)
                {
                    if (figures[i].buildings[j] == building) return i;
                }
            }
            return 5;
        }
    }
}
