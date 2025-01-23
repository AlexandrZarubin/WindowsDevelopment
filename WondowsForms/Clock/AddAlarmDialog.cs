using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock
{
	public partial class AddAlarmDialog : Form
	{
		internal Alarm CreatedAlarm { get; private set; }
		public AddAlarmDialog()
		{
			InitializeComponent();
			dateTimePickerDate.Enabled = false;
		}
		internal AddAlarmDialog(Alarm alarm = null)
		{
			InitializeComponent();

			if (alarm != null)
			{
				// Заполнение данных будильника
				checkBoxUSeDate.Checked = alarm.Date.HasValue;
				if (alarm.Date.HasValue)
					dateTimePickerDate.Value = alarm.Date.Value;
				dateTimePickerTime.Value = DateTime.Today.Add(alarm.Time);
				foreach (DayOfWeek day in alarm.Week)
				{
					int index = (int)day - 1; // Days start from 0 (Sunday)
					if (index >= 0 && index < checkedListBoxWeekDays.Items.Count)
						checkedListBoxWeekDays.SetItemChecked(index, true);
				}
				labelfilename.Text = alarm.Filename;
			}
		}
		private void checkBoxUSeDate_CheckedChanged(object sender, EventArgs e)
		{
			dateTimePickerDate.Enabled=checkBoxUSeDate.Checked;
		}

		private void buttonOk_Click(object sender, EventArgs e)
		{
			var selectedDays = new List<DayOfWeek>();
			for (int i = 0;i< checkedListBoxWeekDays.Items.Count;i++)
			{
				//Console.Write(checkedListBoxWeekDays.GetItemChecked(i)+"\t");
				if (checkedListBoxWeekDays.GetItemChecked(i))
					selectedDays.Add((DayOfWeek)(i + 1));
			}
			CreatedAlarm = new Alarm
			{
				Date = checkBoxUSeDate.Checked ? (DateTime?)dateTimePickerDate.Value : null,
				Time = dateTimePickerTime.Value.TimeOfDay,
				Week = selectedDays,
				Filename = labelfilename.Text,
				Message = "Custom Message" // Добавьте поле для ввода сообщения
			};
			DialogResult = DialogResult.OK;
			//Console.WriteLine();
		}
	}
}
