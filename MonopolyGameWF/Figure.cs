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
        /// <summary>
        /// Кнопка игрока
        /// </summary>
        public Button b;

        /// <summary>
        /// Направление движения
        /// </summary>
        public int direction;

        /// <summary>
        /// ID номер игрока
        /// </summary>
        int manId;

        /// <summary>
        /// Деньги игрока
        /// </summary>
        public int money;

        /// <summary>
        /// Список предприятия игрока
        /// </summary>
        public List<int> buildings;

        /// <summary>
        /// Деньги, получаемые за прохождения круга
        /// </summary>
        public int toEarn;

        /// <summary>
        /// Позиция игрока на поле
        /// </summary>
        public int position;

        /// <summary>
        /// Показатель победы игрока
        /// </summary>
        public bool WIN = false;

        /// <summary>
        /// Конструктор игрока
        /// </summary>
        /// <param name="id">Порядковый номер игрока</param>
        public Figure(int id)
        {
            manId = id;
            direction = 0;
            money = 5000;
            buildings = new List<int>();
            toEarn = 25;
            position = 0;

            b = new Button();
            b.Size = new Size(50, 50);
            b.Text = " ";
            b.Visible = true;
            b.Enabled = false;
            b.FlatStyle = FlatStyle.Flat;
            b.BackgroundImageLayout = ImageLayout.Stretch;

            configure(id);
        }

        /// <summary>
        /// Проверка направления движения
        /// </summary>
        public void checkForDir()
        {
            switch (manId)
            {
                case 0:
                    if (b.Location.X == 700 && b.Location.Y == 0) direction = 1;
                    else if (b.Location.X == 700 && b.Location.Y == 500) direction = 2;
                    else if (b.Location.X == 0 && b.Location.Y == 500) direction = 3;
                    else if (b.Location.X == 0 && b.Location.Y == 0)
                    {
                        direction = 0;
                        money += toEarn;
                        checkIfWon();
                    }
                    break;
                case 1:
                    if (b.Location.X == 750 && b.Location.Y == 0) direction = 1;
                    else if (b.Location.X == 750 && b.Location.Y == 500) direction = 2;
                    else if (b.Location.X == 50 && b.Location.Y == 500) direction = 3;
                    else if (b.Location.X == 50 && b.Location.Y == 0) 
                    { 
                        direction = 0;
                        money += toEarn;
                        checkIfWon();
                    }
                    break;
                case 2:
                    if (b.Location.X == 700 && b.Location.Y == 50) direction = 1;
                    else if (b.Location.X == 700 && b.Location.Y == 550) direction = 2;
                    else if (b.Location.X == 0 && b.Location.Y == 550) direction = 3;
                    else if (b.Location.X == 0 && b.Location.Y == 50)
                    {
                        direction = 0;
                        money += toEarn;
                        checkIfWon();
                    }
                    break;
                case 3:
                    if (b.Location.X == 750 && b.Location.Y == 50) direction = 1;
                    else if (b.Location.X == 750 && b.Location.Y == 550) direction = 2;
                    else if (b.Location.X == 50 && b.Location.Y == 550) direction = 3;
                    else if (b.Location.X == 50 && b.Location.Y == 50)
                    {
                        direction = 0;
                        money += toEarn;
                        checkIfWon();
                    }
                    break;
            }
        }

        /// <summary>
        /// Конфигурация иконки и положения фигурки от порядкового номера игрока
        /// </summary>
        /// <param name="id">Порядковый номер игрока</param>
        private void configure(int id)
        {
            switch (id)
            {
                case 0:
                    b.BackgroundImage = Properties.Resources.first;
                    b.Location = new Point(0, 0);
                    break;
                case 1:
                    b.BackgroundImage = Properties.Resources.second;
                    b.Location = new Point(50, 0);
                    break;
                case 2:
                    b.BackgroundImage = Properties.Resources.third;
                    b.Location = new Point(0, 50);
                    break;
                case 3:
                    b.BackgroundImage = Properties.Resources.fourth;
                    b.Location = new Point(50, 50);
                    break;
            }
        }

        /// <summary>
        /// Проверка условия победы игрока
        /// </summary>
        private void checkIfWon()
        {
            if (money >= 15000)
            {
                WIN = true;
            }
        }
    }
}
