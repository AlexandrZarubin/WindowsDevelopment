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
	public partial class AlaramsDialog : Form
	{
		AddAlarmDialog dialog;
		private List<Alarm> alarms = new List<Alarm>();
		public AlaramsDialog()
		{
			InitializeComponent();
			dialog = new AddAlarmDialog();
		}

		private void RefreshAlarmsList()
		{
			listBoxAlarms.DataSource = null;
			listBoxAlarms.DataSource = alarms;
			listBoxAlarms.DisplayMember = "ToString";
		}
		private void buttonAdd_Click(object sender, EventArgs e)
		{

			//dialog.ShowDialog();
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				alarms.Add(dialog.CreatedAlarm);
				RefreshAlarmsList();
			}
		}

		private void buttonEdit_Click(object sender, EventArgs e)
		{
			if (listBoxAlarms.SelectedItem is Alarm selectedAlarm)
			{
				dialog = new AddAlarmDialog(selectedAlarm);
				if (dialog.ShowDialog() == DialogResult.OK)
				{
					RefreshAlarmsList();
				}
			}
		}

		private void buttonDelete_Click(object sender, EventArgs e)
		{
			if (listBoxAlarms.SelectedItem is Alarm selectedAlarm)
			{
				alarms.Remove(selectedAlarm);
				RefreshAlarmsList();
			}	
		}
	}
}
