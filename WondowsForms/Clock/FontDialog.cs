using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Text;
namespace Clock
{
	public partial class FontDialog : Form
	{
		string execution_path = "";                                                         // Путь до исполняемого файла
		string fonts_path = "";                                                             // Путь до шрифтов
		public string FontsPath { get => fonts_path; }                                      // Свойство для получения пути до шрифтов
		public string FontFilename { get; set; }                                            // Имя файла шрифта
		public Font Font { get; set; }                                                      // Выбранный шрифт
		public FontDialog()                                                                 // Конструктор формы
		{
			InitializeComponent();
			execution_path= Path.GetDirectoryName(Application.ExecutablePath);              // Установка пути
			fonts_path = $"{execution_path}\\..\\..\\Fonts";                                // Путь до шрифтов
			LoadFonts();
		}
		public FontDialog(string fontname,float fontsize):this()                            // Конструктор с параметрами шрифта
		{
			numericUpDownFontSize.Value = (decimal)fontsize;                                // Установка размера шрифта
			comboBoxFonts.SelectedIndex = comboBoxFonts.Items.IndexOf(fontname);            // Поиск шрифта в списке и установка текущего выбранного шрифта
			Font = labelExample.Font;                                                       // Присвоение текущего шрифта
			FontFilename = fontname;                                                        // Присвоение имени файла шрифта
		}
		void LoadFonts()
		{
			Console.WriteLine(execution_path);
			//Directory.SetCurrentDirectory(fonts_path);
			//Console.WriteLine(Directory.GetCurrentDirectory());

			comboBoxFonts.Items.AddRange(GetFontsFromDirectory(fonts_path,"*ttf"));
			comboBoxFonts.Items.AddRange(GetFontsFromDirectory(fonts_path,"*otf"));
			comboBoxFonts.SelectedIndex = 0;												
		}
		string[] GetFontsFromDirectory(string directory,string format)                      // Метод для получения списка шрифтов
		{ 
			string[]fonts=Directory.GetFiles(directory,format);                             // Получение всех файлов с указанным форматом
			for (int i = 0; i <fonts.Length; i++)                                           // Удаление пути из имени файла и оставление только имени
			{
				fonts[i] = fonts[i].Split('\\').Last();
			}
			return fonts;
		}
		void setFont()                                                                      // Метод для установки шрифта в примере
		{
			PrivateFontCollection pfc=new PrivateFontCollection();                          // Создание коллекции шрифтов
			pfc.AddFontFile($"{fonts_path}\\{comboBoxFonts.SelectedItem}");                 // Добавление выбранного шрифта в коллекцию
			labelExample.Font=new Font(pfc.Families[0],Convert.ToInt32(numericUpDownFontSize.Value));   // Установка шрифта и размера 

		}
		private void comboBoxFonts_SelectedIndexChanged(object sender, EventArgs e)         // Обработчик изменения выбранного шрифта
		{
			setFont();
		}

		private void buttonOK_Click(object sender, EventArgs e)
		{
			Font=labelExample.Font;                                                         // Сохранение текущего шрифта
			FontFilename =comboBoxFonts.SelectedItem.ToString();                            // Сохранение имени файла шрифта
		}

		private void buttonApplay_Click(object sender, EventArgs e)                         // Обработчик нажатия кнопки "Применить"
		{
			//setFont();
			Font = labelExample.Font;                                                       // Применение текущего шрифта
			FontFilename = comboBoxFonts.SelectedItem.ToString();                           // Сохранение имени файла шрифта
		}
	}
}
