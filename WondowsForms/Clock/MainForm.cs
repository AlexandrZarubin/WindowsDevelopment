using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

namespace Clock
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
			labelTime.BackColor = Color.AliceBlue;
			this.Location = new Point(Screen.PrimaryScreen.Bounds.Width - this.Width,50);
		}
		void SetVisibility(bool visible)
		{
			checkBoxShowDate.Visible = visible;
			checkBoxShowWeekDay.Visible = visible;
			buttonHideControls.Visible = visible;
			this.FormBorderStyle =visible?FormBorderStyle.FixedDialog: FormBorderStyle.None;
			this.ShowInTaskbar = visible;
			this.TransparencyKey =visible?Color.Empty: this.BackColor;
		}
		private void timer_Tick(object sender, EventArgs e)
		{
			//Обработчик события - это самая обычная функция, которая не явно вызывается при возникновоний определеного события
			// У элемента интерфейса может быть множество событий, и одно из них будет событием по умолчанию
			//labelTime.Text = DateTime.Now.ToString("hh:mm:ss tt",System.Globalization.CultureInfo.InvariantCulture);
			labelTime.Text = DateTime.Now.ToString("HH:mm:ss");
		if(checkBoxShowDate.Checked)
			labelTime.Text+=$"\n{DateTime.Now.ToString("yyyy.MM.dd")}";

		if (checkBoxShowWeekDay.Checked)
			labelTime.Text += $"\n{DateTime.Now.DayOfWeek}";

		}

		private void buttonHideControls_Click(object sender, EventArgs e)
		{
			SetVisibility(false);
		}

		private void labelTime_DoubleClick(object sender, EventArgs e)
		{
			SetVisibility(true);
		}
	}
}
