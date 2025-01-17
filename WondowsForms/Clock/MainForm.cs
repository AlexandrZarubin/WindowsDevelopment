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
using System.Runtime.InteropServices;	//DllImport
using System.IO;						//Directory
namespace Clock
{
	public partial class MainForm : Form
	{
		FontDialog fontDialog;
		public MainForm()
		{
			this.SetStyle(ControlStyles.OptimizedDoubleBuffer|ControlStyles.UserPaint| ControlStyles.AllPaintingInWmPaint, true);
			this.UpdateStyles();
			
			InitializeComponent();
			labelTime.BackColor = Color.AliceBlue;
			this.Location = new Point(Screen.PrimaryScreen.Bounds.Width - this.Width,50);
			ToolStripMenuItemsShowControls.Checked = true; //works not correctly
			//ToolStripMenuItemsShowControls.Checked = false; //works not correctly
			ToolStripMenuItemShowConsole.Checked = true;
			//fontDialog = new FontDialog();

			//Console.WriteLine(Directory.GetCurrentDirectory());
			LoadSettings();
			if (fontDialog == null) fontDialog = new FontDialog();

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
		void LoadSettings()
		{
			StreamReader sr = null;
			try
			{
				sr = new StreamReader($"{Path.GetDirectoryName(Application.ExecutablePath)}\\..\\..\\Settings.ini");
				ToolStripMenuItemTopmost.Checked = Boolean.Parse(sr.ReadLine());
				ToolStripMenuItemsShowControls.Checked = Boolean.Parse(sr.ReadLine());
				ToolStripMenuItemShowConsole.Checked = Boolean.Parse(sr.ReadLine());
				ToolStripMenuItemShowDate.Checked = Boolean.Parse(sr.ReadLine());
				ToolStripMenuItemShowWeekday.Checked = Boolean.Parse(sr.ReadLine());
				string fontname = sr.ReadLine();
				float fontsize = (float)Convert.ToDouble(sr.ReadLine());
				labelTime.BackColor = Color.FromArgb(Convert.ToInt32(sr.ReadLine()));
				labelTime.ForeColor = Color.FromArgb(Convert.ToInt32(sr.ReadLine()));
				//sr.Close();
				fontDialog = new FontDialog(fontname, fontsize);
				labelTime.Font = fontDialog.Font;
			}
			catch (Exception ex)
			{
				MessageBox.Show(this, ex.Message, "In LoadSettings()", MessageBoxButtons.OK, MessageBoxIcon.Error);
				MessageBox.Show(this, ex.ToString(), "In LoadSettings()", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
			finally
			{
				if (sr != null) sr.Close();
			}
		}
		void SaveSettings()
		{
			if (string.IsNullOrEmpty(fontDialog.FontFilename))
			{
				fontDialog.FontFilename = labelTime.Font.FontFamily.Name; // Используем текущий шрифт
			}
			StreamWriter sw = new StreamWriter($"{Path.GetDirectoryName(Application.ExecutablePath)}\\..\\..\\Settings.ini");
			sw.WriteLine($"{ToolStripMenuItemTopmost.Checked}");
			sw.WriteLine($"{ToolStripMenuItemsShowControls.Checked}");
			sw.WriteLine($"{ToolStripMenuItemShowConsole.Checked}");
			sw.WriteLine($"{ToolStripMenuItemShowDate.Checked}");
			sw.WriteLine($"{ToolStripMenuItemShowWeekday.Checked}");
			//sw.WriteLine($"{comboBoxFonts.SelectedItem}")
			sw.WriteLine($"{fontDialog.FontFilename}");
			sw.WriteLine($"{labelTime.Font.Size}");
			sw.WriteLine($"{labelTime.BackColor.ToArgb()}");
			sw.WriteLine($"{labelTime.ForeColor.ToArgb()}");
			sw.Close();
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
			if (colorDialog.ShowDialog(this) == DialogResult.OK)labelTime.ForeColor = colorDialog.Color;
		}

		private void ToolStripMenuItemChooseFont_Click(object sender, EventArgs e)
		{
			if(fontDialog.ShowDialog(this)==DialogResult.OK);
			{
				labelTime.Font = fontDialog.Font;
			}
		}

		private void notifyIcon_DoubleClick(object sender, EventArgs e)
		{
			if(!this.TopMost)
			{
				this.TopMost= true;
				this.TopMost= false;
			}
		}

		private void ToolStripMenuItemShowConsole_CheckedChanged(object sender, EventArgs e)
		{
			bool show=ToolStripMenuItemShowConsole.Checked? AllocConsole(): FreeConsole();
			//AllocConsole();
		}
		[DllImport("kernel32.dll")]
		static extern bool AllocConsole();
		[DllImport("kernel32.dll")]
		static extern bool FreeConsole();

		private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
		{
			SaveSettings();
		}


		//private void ToolStripMenuItemsShowControls_CheckedChanged(object sender, EventArgs e)
		//{
		//	SetVisibility(ToolStripMenuItemsShowControls.Checked);	
		//}


	}
}
