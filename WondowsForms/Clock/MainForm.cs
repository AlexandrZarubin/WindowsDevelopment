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
			ToolStripMenuItemsShowControls.Checked = true; //works not correctly
			//ToolStripMenuItemsShowControls.Checked = false; //works not correctly
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

		//notifyIcon.Text = labelTime.Text;
		notifyIcon.Text = $"{ DateTime.Now.ToString("HH:mm:ss")}\n{DateTime.Now.ToString("yyyy.MM.dd")}\n{DateTime.Now.DayOfWeek}";
		}

		private void buttonHideControls_Click(object sender, EventArgs e)
		{
			//SetVisibility(false);
			ToolStripMenuItemsShowControls.Checked = false;
		}

		private void labelTime_DoubleClick(object sender, EventArgs e)
		{
			//SetVisibility(true);
			ToolStripMenuItemsShowControls.Checked = true;
		}

		//private void ToolStripMenuItemExit_Click(object sender, EventArgs e)=>this.Close();
		private void ToolStripMenuItemExit_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void ToolStripMenuItemTopmost_CheckedChanged(object sender, EventArgs e)=> this.TopMost = ToolStripMenuItemTopmost.Checked;

		private void ToolStripMenuItemsShowControls_CheckStateChanged(object sender, EventArgs e)
		{
			SetVisibility(ToolStripMenuItemsShowControls.Checked);
		}

		private void ToolStripMenuItemShowDate_CheckedChanged(object sender, EventArgs e)
		{
			checkBoxShowDate.Checked = ToolStripMenuItemShowDate.Checked;
		}

		private void checkBoxShowDate_CheckedChanged(object sender, EventArgs e)
		{
			ToolStripMenuItemShowDate.Checked=checkBoxShowDate.Checked;
		}

		private void ToolStripMenuItemShowWeekday_CheckedChanged(object sender, EventArgs e)
		{
			checkBoxShowWeekDay.Checked=ToolStripMenuItemShowWeekday.Checked;
		}

		private void checkBoxShowWeekDay_CheckedChanged(object sender, EventArgs e)
		{
			ToolStripMenuItemShowWeekday.Checked=checkBoxShowWeekDay.Checked;
		}

		private void ToolStripMenuItemBackroundColor_Click(object sender, EventArgs e)
		{
			colorDialog.Color=labelTime.BackColor;
			DialogResult result=colorDialog.ShowDialog(this);
			if (result == DialogResult.OK) labelTime.BackColor = colorDialog.Color;

        }

		private void ToolStripMenuItemForegroundColor_Click(object sender, EventArgs e)
		{
			colorDialog.Color = labelTime.ForeColor;
			if (colorDialog.ShowDialog(this) == DialogResult.OK) ;labelTime.ForeColor = colorDialog.Color;
		}



		//private void ToolStripMenuItemsShowControls_CheckedChanged(object sender, EventArgs e)
		//{
		//	SetVisibility(ToolStripMenuItemsShowControls.Checked);	
		//}


	}
}
