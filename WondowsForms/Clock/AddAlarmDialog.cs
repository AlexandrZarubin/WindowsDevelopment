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
		public AddAlarmDialog()
		{
			InitializeComponent();
			dateTimePickerDate.Enabled = false;
			this.StartPosition = FormStartPosition.Manual;
		}

		private void checkBoxUSeDate_CheckedChanged(object sender, EventArgs e)
		{
			dateTimePickerDate.Enabled=checkBoxUSeDate.Checked;
		}

		private void buttonOk_Click(object sender, EventArgs e)
		{
			for(int i = 0;i< checkedListBoxWeekDays.Items.Count;i++)
			{
				Console.Write(checkedListBoxWeekDays.GetItemChecked(i)+"\t");
            }
                Console.WriteLine();
		}
	}
}
