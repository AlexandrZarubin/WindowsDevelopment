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
		public AlaramsDialog()
		{
			InitializeComponent();
			dialog = new AddAlarmDialog();
		}

		private void buttonAdd_Click(object sender, EventArgs e)
		{

			dialog.ShowDialog();
		}
	}
}
