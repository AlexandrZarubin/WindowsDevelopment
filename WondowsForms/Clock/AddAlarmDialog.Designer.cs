namespace Clock
{
	partial class AddAlarmDialog
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AddAlarmDialog));
			this.checkBoxUSeDate = new System.Windows.Forms.CheckBox();
			this.dateTimePickerDate = new System.Windows.Forms.DateTimePicker();
			this.dateTimePickerTime = new System.Windows.Forms.DateTimePicker();
			this.checkedListBoxWeekDays = new System.Windows.Forms.CheckedListBox();
			this.labelfilename = new System.Windows.Forms.Label();
			this.buttonOk = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// checkBoxUSeDate
			// 
			this.checkBoxUSeDate.AutoSize = true;
			this.checkBoxUSeDate.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.checkBoxUSeDate.Location = new System.Drawing.Point(13, 13);
			this.checkBoxUSeDate.Name = "checkBoxUSeDate";
			this.checkBoxUSeDate.Size = new System.Drawing.Size(120, 29);
			this.checkBoxUSeDate.TabIndex = 0;
			this.checkBoxUSeDate.Text = "Use Date";
			this.checkBoxUSeDate.UseVisualStyleBackColor = true;
			this.checkBoxUSeDate.CheckedChanged += new System.EventHandler(this.checkBoxUSeDate_CheckedChanged);
			// 
			// dateTimePickerDate
			// 
			this.dateTimePickerDate.CustomFormat = "yyyy.MM.dd";
			this.dateTimePickerDate.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.dateTimePickerDate.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
			this.dateTimePickerDate.Location = new System.Drawing.Point(13, 59);
			this.dateTimePickerDate.Name = "dateTimePickerDate";
			this.dateTimePickerDate.Size = new System.Drawing.Size(169, 31);
			this.dateTimePickerDate.TabIndex = 1;
			// 
			// dateTimePickerTime
			// 
			this.dateTimePickerTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.dateTimePickerTime.Format = System.Windows.Forms.DateTimePickerFormat.Time;
			this.dateTimePickerTime.Location = new System.Drawing.Point(188, 59);
			this.dateTimePickerTime.Name = "dateTimePickerTime";
			this.dateTimePickerTime.Size = new System.Drawing.Size(169, 31);
			this.dateTimePickerTime.TabIndex = 2;
			// 
			// checkedListBoxWeekDays
			// 
			this.checkedListBoxWeekDays.CheckOnClick = true;
			this.checkedListBoxWeekDays.ColumnWidth = 48;
			this.checkedListBoxWeekDays.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.checkedListBoxWeekDays.FormattingEnabled = true;
			this.checkedListBoxWeekDays.Items.AddRange(new object[] {
            "Пн",
            "Вт",
            "Ср",
            "Чт",
            "Пт",
            "Сб",
            "Вс"});
			this.checkedListBoxWeekDays.Location = new System.Drawing.Point(13, 112);
			this.checkedListBoxWeekDays.MultiColumn = true;
			this.checkedListBoxWeekDays.Name = "checkedListBoxWeekDays";
			this.checkedListBoxWeekDays.Size = new System.Drawing.Size(344, 25);
			this.checkedListBoxWeekDays.TabIndex = 3;
			// 
			// labelfilename
			// 
			this.labelfilename.AutoSize = true;
			this.labelfilename.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.labelfilename.Location = new System.Drawing.Point(25, 165);
			this.labelfilename.Name = "labelfilename";
			this.labelfilename.Size = new System.Drawing.Size(100, 25);
			this.labelfilename.TabIndex = 4;
			this.labelfilename.Text = "Filename";
			// 
			// buttonOk
			// 
			this.buttonOk.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.buttonOk.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.buttonOk.Location = new System.Drawing.Point(154, 281);
			this.buttonOk.Name = "buttonOk";
			this.buttonOk.Size = new System.Drawing.Size(103, 36);
			this.buttonOk.TabIndex = 5;
			this.buttonOk.Text = "Ok";
			this.buttonOk.UseVisualStyleBackColor = true;
			this.buttonOk.Click += new System.EventHandler(this.buttonOk_Click);
			// 
			// buttonCancel
			// 
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.buttonCancel.Location = new System.Drawing.Point(263, 281);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(103, 35);
			this.buttonCancel.TabIndex = 6;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.UseVisualStyleBackColor = true;
			// 
			// AddAlarmDialog
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(394, 351);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOk);
			this.Controls.Add(this.labelfilename);
			this.Controls.Add(this.checkedListBoxWeekDays);
			this.Controls.Add(this.dateTimePickerTime);
			this.Controls.Add(this.dateTimePickerDate);
			this.Controls.Add(this.checkBoxUSeDate);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "AddAlarmDialog";
			this.ShowInTaskbar = false;
			this.Text = "AddAlarmDialog";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.CheckBox checkBoxUSeDate;
		private System.Windows.Forms.DateTimePicker dateTimePickerDate;
		private System.Windows.Forms.DateTimePicker dateTimePickerTime;
		private System.Windows.Forms.CheckedListBox checkedListBoxWeekDays;
		private System.Windows.Forms.Label labelfilename;
		private System.Windows.Forms.Button buttonOk;
		private System.Windows.Forms.Button buttonCancel;
	}
}