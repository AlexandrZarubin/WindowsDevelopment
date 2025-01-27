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
		public ListBox Alarms { get => listBoxAlarms; }
		public AlaramsDialog()
		{
			InitializeComponent();
			dialog = new AddAlarmDialog();
		}
		public AlaramsDialog(System.Windows.Forms.Form parent):this()
		{
			this.StartPosition = FormStartPosition.Manual;	
			this.Location=new Point(
				parent.Location.X-this.Width,
				parent.Location.Y+(this.Height) );
		}
		private void buttonAdd_Click(object sender, EventArgs e)
		{
			dialog.Location = new Point
				(
				this.Location.X + (this.Width - dialog.Width) / 2,
				this.Location.Y + (this.Height - dialog.Height) / 2
				);
			DialogResult result=dialog.ShowDialog();
			if (result == DialogResult.OK)
			{
				listBoxAlarms.Items.Add(new Alarm(dialog.Alarm) );
			}
		}

		private void listBoxAlarms_DoubleClick(object sender, EventArgs e)
		{
			if (listBoxAlarms.SelectedItem == null) return;
			dialog.Alarm=listBoxAlarms.SelectedItem as Alarm;
			//dialog.ShowDialog();
			//listBoxAlarms.SelectedItem = null;
			//listBoxAlarms.SelectedItem=dialog.Alarm;
			//listBoxAlarms.Refresh();
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				//int selectedIndex = listBoxAlarms.SelectedIndex;
				//listBoxAlarms.Items.RemoveAt(selectedIndex);
				//listBoxAlarms.Items.Insert(selectedIndex, dialog.Alarm);
				listBoxAlarms.Items[listBoxAlarms.SelectedIndex] = dialog.Alarm;
			}

		}

		private void listBoxAlarms_SelectedIndexChanged(object sender, EventArgs e)
		{
			if(listBoxAlarms.SelectedItems!=null)
			labelAlarmInfo.Text=listBoxAlarms.SelectedItem.ToString();
		}
	}
}
