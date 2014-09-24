/*
 * Olimex WPC 65 - PCB track resistance calculator
 * 
 * Mono 2.10.8.1
 * Monodevelop 3.0.3.2
 * GTK# 2.12.0.0
 * 
 */

using System;
using Gtk;

namespace rescalc
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			Application.Init ();
			MainWindow win = new MainWindow ();
			win.Show ();
			Application.Run ();
		}
	}
}
