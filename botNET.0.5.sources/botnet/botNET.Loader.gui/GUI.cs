using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

using System.Diagnostics;

namespace botNET.Loader
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class GUI : System.Windows.Forms.Form
	{
		private System.Windows.Forms.CheckedListBox chlPList;
		private System.Windows.Forms.Button btnRefresh;
		private System.Windows.Forms.Button btnKill;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public GUI()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//

			this.D2Refresh();
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.chlPList = new System.Windows.Forms.CheckedListBox();
			this.btnRefresh = new System.Windows.Forms.Button();
			this.btnKill = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// chlPList
			// 
			this.chlPList.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.chlPList.Location = new System.Drawing.Point(8, 8);
			this.chlPList.Name = "chlPList";
			this.chlPList.Size = new System.Drawing.Size(320, 124);
			this.chlPList.TabIndex = 0;
			this.chlPList.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.chlPList_ItemCheck);
			// 
			// btnRefresh
			// 
			this.btnRefresh.Location = new System.Drawing.Point(88, 144);
			this.btnRefresh.Name = "btnRefresh";
			this.btnRefresh.TabIndex = 1;
			this.btnRefresh.Text = "Refresh";
			this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
			// 
			// btnKill
			// 
			this.btnKill.Location = new System.Drawing.Point(173, 144);
			this.btnKill.Name = "btnKill";
			this.btnKill.TabIndex = 2;
			this.btnKill.Text = "Kill";
			this.btnKill.Click += new System.EventHandler(this.btnKill_Click);
			// 
			// GUI
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(336, 173);
			this.Controls.Add(this.btnKill);
			this.Controls.Add(this.btnRefresh);
			this.Controls.Add(this.chlPList);
			this.Name = "GUI";
			this.Text = "botNET Loader";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new GUI());
		}

		void D2Refresh()
		{
			try
			{
				chlPList.Items.Clear();
				Process[] processes = Process.GetProcessesByName("Diablo II");
				foreach(Process p in processes)
				{
					PListItem pl = new PListItem(p);
					bool chk = false;
					foreach(ProcessModule pm in p.Modules)
					{
						if(pm.FileName.ToLower().EndsWith("botnet.dll"))
						{
							chk = true;
							break;
						}
					}

					chlPList.Items.Add(pl, chk?CheckState.Checked:CheckState.Unchecked);

				}
				processes = Process.GetProcessesByName("Game");
				foreach(Process p in processes)
				{
					PListItem pl = new PListItem(p);
					bool chk = false;
					foreach(ProcessModule pm in p.Modules)
					{
						//MessageBox.Show(pm.mo
						if(pm.FileName.ToLower().EndsWith("botnet.dll"))
						{
							chk = true;
							break;
						}
					}

					chlPList.Items.Add(pl, chk?CheckState.Checked:CheckState.Unchecked);

				}
				processes = Process.GetProcessesByName("D2Loader");
				foreach(Process p in processes)
				{
					PListItem pl = new PListItem(p);
					bool chk = false;
					foreach(ProcessModule pm in p.Modules)
					{
						//MessageBox.Show(pm.mo
						if(pm.FileName.ToLower().EndsWith("botnet.dll"))
						{
							chk = true;
							break;
						}
					}

					chlPList.Items.Add(pl, chk?CheckState.Checked:CheckState.Unchecked);
				}
			}
			catch (Exception e)
			{
				MessageBox.Show ("An exception occured while searching for Diablo II: " + e.Message + "\r\n\r\n" + e.StackTrace);
			}
		}

		private void btnRefresh_Click(object sender, System.EventArgs e)
		{
			this.D2Refresh();
		}

		private void chlPList_ItemCheck(object sender, System.Windows.Forms.ItemCheckEventArgs e)
		{
			if (chlPList.SelectedIndex == -1)
				return;

			/*if(e.CurrentValue == CheckState.Checked)
			{
				e.NewValue = CheckState.Checked;
				MessageBox.Show("At this time, botNET cannot be unloaded");
				return;
			}*/

			Process p = ((PListItem)chlPList.Items[e.Index]).Proc;
			this.chlPList.Enabled = false;
			if(Loader.Go(p.Handle, Convert.ToUInt32(p.MainModule.BaseAddress.ToInt32()), p.MainWindowHandle))
			{
				//e.NewValue = CheckState.Checked;
				this.D2Refresh();
			}
			else
			{
				MessageBox.Show("Load Failed");
				//e.NewValue = CheckState.Unchecked;
				this.D2Refresh();
			}
			this.chlPList.Enabled = true;
		}

		private void btnKill_Click(object sender, System.EventArgs e)
		{
			if(chlPList.SelectedIndex < 0) return;
			Process p = ((PListItem)chlPList.Items[chlPList.SelectedIndex]).Proc;
			if(!p.HasExited)
				p.Kill();
			System.Threading.Thread.Sleep(1000);
			this.D2Refresh();
		}


	}



}













