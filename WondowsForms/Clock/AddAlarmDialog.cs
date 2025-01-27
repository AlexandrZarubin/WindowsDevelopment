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
		public Alarm Alarm;
		OpenFileDialog openFile;
		public AddAlarmDialog()
		{
			InitializeComponent();
			dateTimePickerDate.Enabled = false;
			this.StartPosition = FormStartPosition.Manual;
			Alarm=new Alarm();
			SetWeekDays();
			openFile=new OpenFileDialog();
			labelfilename.Height = 32;
		}
		void SetWeekDays()
		{
			bool[]days=Alarm.Week.ToArray();
			for (int i = 0; i < checkedListBoxWeekDays.Items.Count; i++)
			{
				checkedListBoxWeekDays.SetItemChecked(i,days[i]);
			}
		}
		private void checkBoxUSeDate_CheckedChanged(object sender, EventArgs e)
		{
			dateTimePickerDate.Enabled=checkBoxUSeDate.Checked;
			checkedListBoxWeekDays.Enabled = !checkBoxUSeDate.Checked;
		}

		private void buttonOk_Click(object sender, EventArgs e)
		{
			this.DialogResult=DialogResult.OK;
			Alarm.Date = dateTimePickerDate.Enabled ? dateTimePickerDate.Value : DateTime.MinValue;
			Alarm.Time = dateTimePickerTime.Value.TimeOfDay;
			//for(int i = 0;i< checkedListBoxWeekDays.Items.Count;i++)
			//{
			//	Console.Write(checkedListBoxWeekDays.GetItemChecked(i)+"\t");
			// }
			//  Console.WriteLine();
			Alarm.Week = new Week
				(
					checkedListBoxWeekDays.Items.Cast<object>().
					Select((item, index) => checkedListBoxWeekDays.GetItemChecked(index)).ToArray()
				);
			if (labelfilename.Text != "Filename" && labelfilename.Text != "")
			{
				Alarm.Filename = openFile.FileName;
			}
			else
			{
				MessageBox.Show(this, "Выберите звуковой фаил", "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
				this.DialogResult= DialogResult.None;
			}
			Alarm.Message=richTextBoxMessage.Text;
		}

		private void buttonChooseFile_Click(object sender, EventArgs e)
		{
			if (openFile.ShowDialog() == DialogResult.OK)
			{
				labelfilename.Text = $"Filename\n{openFile.FileName}";
			}
		}
	}
}
