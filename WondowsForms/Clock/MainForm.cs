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
using System.IO;                        //Directory
using Microsoft.Win32;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Clock
{
	public partial class MainForm : Form
	{
		FontDialog fontDialog;                                                                  // Диалоговое окно для выбора шрифта
		AlaramsDialog alarmsDialog;
		Alarm nextAlarm;
		public MainForm()																		// Конструктор формы
		{
			// Оптимизация отрисовки
			//this.SetStyle(ControlStyles.OptimizedDoubleBuffer|ControlStyles.UserPaint|ControlStyles.AllPaintingInWmPaint, true);
			//this.UpdateStyles();                                                                // Применение стилей

			InitializeComponent();
			labelTime.BackColor = Color.AliceBlue;												// Установка фона для label
			this.Location = new Point(Screen.PrimaryScreen.Bounds.Width - this.Width,50);       // Размещение окна
			ToolStripMenuItemsShowControls.Checked = true;		//works not correctly			// Отображение контролов
			//ToolStripMenuItemsShowControls.Checked = false;	//works not correctly			// Отображение консоли
			ToolStripMenuItemShowConsole.Checked = true;										// Проверка и создание диалога шрифта
			//fontDialog = new FontDialog();

			//Console.WriteLine(Directory.GetCurrentDirectory());
			LoadSettings();
			alarmsDialog = new AlaramsDialog(this);
			if (fontDialog == null) fontDialog = new FontDialog();
			axWindowsMediaPlayer.Visible = false;
			

        }
		void SetVisibility(bool visible)                                                        // Установка видимости контролов
		{
			checkBoxShowDate.Visible = visible;                                                 // Видимость чекбокса отображения даты
			checkBoxShowWeekDay.Visible = visible;                                              // Видимость чекбокса отображения дня недели
			buttonHideControls.Visible = visible;                                               // Видимость кнопки скрытия контролов
			this.FormBorderStyle =visible?FormBorderStyle.FixedDialog: FormBorderStyle.None;    // Установка стиля границы формы в зависимости от видимости
			this.ShowInTaskbar = visible;                                                       // Отображение в панели задач
			this.TransparencyKey =visible?Color.Empty: this.BackColor;                          // Установка прозрачности
		}
		void LoadSettings()
		{
			StreamReader sr = null;
			try
			{
				sr = new StreamReader($"{Path.GetDirectoryName(Application.ExecutablePath)}\\..\\..\\Settings.ini");    // Открытие файла с настройками
				ToolStripMenuItemTopmost.Checked = Boolean.Parse(sr.ReadLine());                // Загрузка настройки "Поверх всех окон"
				ToolStripMenuItemsShowControls.Checked = Boolean.Parse(sr.ReadLine());          // Загрузка настройки отображения контролов
				ToolStripMenuItemShowConsole.Checked = Boolean.Parse(sr.ReadLine());            // Загрузка настройки отображения консоли
				ToolStripMenuItemShowDate.Checked = Boolean.Parse(sr.ReadLine());               // Загрузка настройки отображения даты
				ToolStripMenuItemShowWeekday.Checked = Boolean.Parse(sr.ReadLine());            // Загрузка настройки отображения дня недели
				string fontname = sr.ReadLine();                                                // Загрузка параметров шрифта
				float fontsize = (float)Convert.ToDouble(sr.ReadLine());
				labelTime.BackColor = Color.FromArgb(Convert.ToInt32(sr.ReadLine()));           // Установка цвета фона метки
				labelTime.ForeColor = Color.FromArgb(Convert.ToInt32(sr.ReadLine()));           // Установка цвета текста метки
				//sr.Close();
				fontDialog = new FontDialog(fontname, fontsize);                                // Создаем диалог шрифта с параметрами
				labelTime.Font = fontDialog.Font;                                               // Установка шрифта для метки
			}
			catch (Exception ex)
			{
				MessageBox.Show(this, ex.Message, "In LoadSettings()", MessageBoxButtons.OK, MessageBoxIcon.Error);
				MessageBox.Show(this, ex.ToString(), "In LoadSettings()", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
			finally                                                                             // Закрываем поток
			{
				if(sr != null) sr.Close();
			}
		}
		void SaveSettings()
		{
			if (string.IsNullOrEmpty(fontDialog.FontFilename))
			{
				fontDialog.FontFilename = labelTime.Font.FontFamily.Name; // Используем текущий шрифт
			}
			StreamWriter sw = new StreamWriter($@"{Path.GetDirectoryName(Application.ExecutablePath)}\..\..\Settings.ini");
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
		Alarm FindNextAlarm()
		{
			nextAlarm=alarmsDialog.Alarms.Items.Cast<Alarm>().ToArray().Min();
			return nextAlarm;
		}
		private void timer_Tick(object sender, EventArgs e)                         // Обновление времени
		{
			//Обработчик события - это самая обычная функция, которая не явно вызывается при возникновоний определеного события
			// У элемента интерфейса может быть множество событий, и одно из них будет событием по умолчанию
			//labelTime.Text = DateTime.Now.ToString("hh:mm:ss tt",System.Globalization.CultureInfo.InvariantCulture);
			labelTime.Text = DateTime.Now.ToString("HH:mm:ss");
		if(checkBoxShowDate.Checked)                                                // Если выбрано отображение даты
			labelTime.Text+=$"\n{DateTime.Now.ToString("yyyy.MM.dd")}";

		if (checkBoxShowWeekDay.Checked)                                            // Если выбрано отображение дня недели
			labelTime.Text += $"\n{DateTime.Now.DayOfWeek}";

			//notifyIcon.Text = labelTime.Text;
			// Обновление текста в уведомлении
			notifyIcon.Text = $"{ DateTime.Now.ToString("HH:mm:ss")}\n{DateTime.Now.ToString("yyyy.MM.dd")}\n{DateTime.Now.DayOfWeek}";

			nextAlarm = FindNextAlarm();
			if(nextAlarm!=null)Console.WriteLine(nextAlarm);
			if(
				nextAlarm!=null&&
				nextAlarm.Time.Hours==DateTime.Now.Hour&&
				nextAlarm.Time.Minutes==DateTime.Now.Minute&&
				nextAlarm.Time.Seconds==DateTime.Now.Second
				)
			{
				System.Threading.Thread.Sleep(1000);
				axWindowsMediaPlayer.Visible = true;
				axWindowsMediaPlayer.URL = nextAlarm.Filename;
				axWindowsMediaPlayer.settings.volume = 100;
				axWindowsMediaPlayer.Ctlcontrols.play();
				if(nextAlarm.Message!="")MessageBox.Show(this,nextAlarm.Message,"Alarm",MessageBoxButtons.OK, MessageBoxIcon.Information);
			}
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

		// Установка "Поверх всех окон"
		private void ToolStripMenuItemTopmost_CheckedChanged(object sender, EventArgs e)=> this.TopMost = ToolStripMenuItemTopmost.Checked;

		private void ToolStripMenuItemsShowControls_CheckStateChanged(object sender, EventArgs e)
		{
			SetVisibility(ToolStripMenuItemsShowControls.Checked);                                          // Управление видимостью контролов
		}

		private void ToolStripMenuItemShowDate_CheckedChanged(object sender, EventArgs e)
		{
			checkBoxShowDate.Checked = ToolStripMenuItemShowDate.Checked;                                   // Синхронизация с чекбоксом даты
		}

		private void checkBoxShowDate_CheckedChanged(object sender, EventArgs e)
		{
			ToolStripMenuItemShowDate.Checked=checkBoxShowDate.Checked;                                     // Синхронизация с меню
		}

		private void ToolStripMenuItemShowWeekday_CheckedChanged(object sender, EventArgs e)
		{
			checkBoxShowWeekDay.Checked=ToolStripMenuItemShowWeekday.Checked;                               // Синхронизация с чекбоксом дня недели
		}

		private void checkBoxShowWeekDay_CheckedChanged(object sender, EventArgs e)
		{
			ToolStripMenuItemShowWeekday.Checked=checkBoxShowWeekDay.Checked;                               // Синхронизация с меню		
		}

		private void ToolStripMenuItemBackroundColor_Click(object sender, EventArgs e)
		{
			colorDialog.Color=labelTime.BackColor;                                                          // Задание начального цвета диалога
			DialogResult result=colorDialog.ShowDialog(this);
			if (result == DialogResult.OK) labelTime.BackColor = colorDialog.Color;                         // Установка нового цвета фона

		}

		private void ToolStripMenuItemForegroundColor_Click(object sender, EventArgs e)
		{
			colorDialog.Color = labelTime.ForeColor;                                                        // Задание начального цвета текста
			if (colorDialog.ShowDialog(this) == DialogResult.OK)labelTime.ForeColor = colorDialog.Color;    // Установка нового цвета текста
		}

		private void ToolStripMenuItemChooseFont_Click(object sender, EventArgs e)
		{
			if(fontDialog.ShowDialog(this)==DialogResult.OK);
			{
				labelTime.Font = fontDialog.Font;												  // Установка нового шрифта	
			}
		}

		private void notifyIcon_DoubleClick(object sender, EventArgs e)						 // Принудительное обновление формы, чтобы избежать проблем отображения
		{
			if(!this.TopMost)
			{
				this.TopMost= true;
				this.TopMost= false;
			}
		}

		private void ToolStripMenuItemShowConsole_CheckedChanged(object sender, EventArgs e)        // Включение или отключение консоли
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

		private void ToolStripMenuItemAlarams_Click(object sender, EventArgs e)
		{
			//AlaramsDialog alarmsDialog = new AlaramsDialog();
			alarmsDialog.ShowDialog();
		}

		private void ToolStripMenuItemLoadOnWindowsStartup_CheckedChanged(object sender, EventArgs e)
		{
			string key_name = "Clock_VPD_311";
			RegistryKey Key=Registry.CurrentUser.OpenSubKey(@"SOFTWARE\Microsoft\Windows\CurrentVersion\Run", true);//true - writable
			if (ToolStripMenuItemLoadOnWindowsStartup.Checked) Key.SetValue(key_name, Application.ExecutablePath);	
			else Key.DeleteValue(key_name, false);                                              //false - throwOnMissingValue
			Key.Dispose();
		}


		//private void ToolStripMenuItemsShowControls_CheckedChanged(object sender, EventArgs e)
		//{
		//	SetVisibility(ToolStripMenuItemsShowControls.Checked);	
		//}


	}
}
