using System;
using System.Windows.Forms;
using System.Drawing;
using System.Net;
using HtmlAgilityPack;
using System.Threading;
using Microsoft.Win32;

namespace notifyicon
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        void rolecalistirma(string url)
        {
            Uri ourUri = new Uri(url);
            WebRequest myWebRequest = WebRequest.Create(url);
            WebResponse myWebResponse = myWebRequest.GetResponse();
            myWebResponse.Close();
        }

        string evip= "IP";

        void guncelle()
        {
            Uri url = new Uri("http://"+ evip +"/");

            WebClient client = new WebClient();
            string html = client.DownloadString(url);
            HtmlAgilityPack.HtmlDocument dokuman = new HtmlAgilityPack.HtmlDocument();
            dokuman.LoadHtml(html);
            HtmlNodeCollection roleler = dokuman.DocumentNode.SelectNodes("//a");
            int role1baslangic = html.IndexOf("1 Durum: ") + 9;
            int role2baslangic = html.IndexOf("2 Durum: ") + 9;
            int role3baslangic = html.IndexOf("3 Durum: ") + 9;
            int role4baslangic = html.IndexOf("4 Durum: ") + 9;

            roledurum[0] = html.Substring(role1baslangic, 1);
            roledurum[1] = html.Substring(role2baslangic, 1);
            roledurum[2] = html.Substring(role3baslangic, 1);
            roledurum[3] = html.Substring(role4baslangic, 1);
            if (roledurum[0] == "K")
            {
                button2.BackColor = Color.FromArgb(255,52,73,94);
                button2.Enabled = true;
                button2.Text = "KAPALI";

            }
            else if(roledurum[0] == "A")
            {
                button2.BackColor = Color.FromArgb(255, 26, 188, 156);
                button2.Enabled = true;
                button2.Text = "AÇIK";
            }

            if (roledurum[1] == "K")
            {
                button4.BackColor = Color.FromArgb(255, 52, 73, 94);
                button4.Enabled = true;
                button4.Text = "KAPALI";

            }
            else if (roledurum[1] == "A")
            {
                button4.BackColor = Color.FromArgb(255, 26, 188, 156);
                button4.Enabled = true;
                button4.Text = "AÇIK";
            }

            if (roledurum[2] == "K")
            {
                button5.BackColor = Color.FromArgb(255, 52, 73, 94);
                button5.Enabled = true;
                button5.Text = "KAPALI";

            }
            else if (roledurum[2] == "A")
            {
                button5.BackColor = Color.FromArgb(255, 26, 188, 156);
                button5.Enabled = true;
                button5.Text = "AÇIK";
            }

            if (roledurum[3] == "K")
            {
                button6.BackColor = Color.FromArgb(255, 52, 73, 94);
                button6.Enabled = true;
                button6.Text = "KAPALI";

            }
            else if (roledurum[3] == "A")
            {
                button6.BackColor = Color.FromArgb(255, 26, 188, 156);
                button6.Enabled = true;
                button6.Text = "AÇIK";
            }
        }
        string[] roledurum = new string[4];

        private void Form1_Load(object sender, EventArgs e)
        {
            guncelle();
            

            chromiumWebBrowser1.LoadUrl("http://" + evip + "/#colorspace");
            
        }

        private void chromiumWebBrowser1_FrameLoadEnd(object sender, CefSharp.FrameLoadEndEventArgs e)
        {
            var script = "var css='body { overflow-x: hidden; overflow-y: hidden;} }'; " +
"var head = document.head || document.getElementsByTagName('head')[0]; var style = document.createElement('style'); style.type = 'text/css'; if (style.styleSheet){ style.styleSheet.cssText = css} else { style.appendChild(document.createTextNode(css)); head.appendChild(style);}";

            if(e.Frame.IsMain)
            {
                e.Browser.MainFrame.ExecuteJavaScriptAsync(script);
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (button2.Text == "KAPALI")
                rolecalistirma("http://" + evip + "/role1ac");
            else if (button2.Text == "AÇIK")
                rolecalistirma("http://" + evip + "/role1kapat");
            
            guncelle();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (button4.Text == "KAPALI")
                rolecalistirma("http://" + evip + "/role2ac");
            else if (button4.Text == "AÇIK")
                rolecalistirma("http://" + evip + "/role2kapat");

            guncelle();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (button5.Text == "KAPALI")
                rolecalistirma("http://" + evip + "/role3ac");
            else if (button5.Text == "AÇIK")
                rolecalistirma("http://" + evip + "/role3kapat");

            guncelle();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (button6.Text == "KAPALI")
                rolecalistirma("http://" + evip + "/role4ac");
            else if (button6.Text == "AÇIK")
                rolecalistirma("http://" + evip + "/role4kapat");

            guncelle();
        }
        bool Mov;
        int MovX, MovY;
        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            Mov = true;
            MovX = e.X;
            MovY = e.Y;
        }        

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (Mov)
            {
                this.SetDesktopLocation(MousePosition.X-MovX, MousePosition.Y - MovY);
            }
        }

        private void kapatToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void göserToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Show();
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.Show();
        }

        private void contextMenuStrip1_Opening(object sender, System.ComponentModel.CancelEventArgs e)
        {

        }

        private void açToolStripMenuItem_Click(object sender, EventArgs e)
        {
            RegistryKey rk = Registry.CurrentUser.OpenSubKey
            ("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);
            
            rk.SetValue("VTL Akıllı Ev Sistemi", Application.ExecutablePath); 
        }

        private void kapatToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            RegistryKey rk = Registry.CurrentUser.OpenSubKey
            ("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);

            rk.DeleteValue("VTL Akıllı Ev Sistemi", false);
        }

        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            Mov = false;
        }
    }
}
