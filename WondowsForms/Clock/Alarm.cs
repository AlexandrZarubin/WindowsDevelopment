using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Clock
{
	internal class Alarm
	{
		public DateTime? Date {  get; set; }
		public TimeSpan Time { get; set; }
		public List<DayOfWeek>Week { get; set; }
		public string Filename { get; set; }
		public string Message { get; set; }

		public override string ToString()
		{
			string days = Week != null && Week.Any()
				? string.Join(", ", Week) : "No days selected";
			return $"{Date?.ToString("yyyy.MM.dd") ?? "No date"}, {Time} ({days}) - {Message}";
			
		}
	}
}
