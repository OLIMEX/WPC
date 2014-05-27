#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
import wx
import urllib
from bs4 import BeautifulSoup

class MainFrame(wx.Frame):
    def __init__(self, *args, **kwds):
        kwds["style"] = wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, *args, **kwds)
        self.label_1 = wx.StaticText(self, -1, "URL:")
        self.text_ctrl_1 = wx.TextCtrl(self, -1, "")
        self.dummy = wx.StaticText(self, -1, "")
        self.button_1 = wx.Button(self, -1, "Go")
        self.text_ctrl_2 = wx.TextCtrl(self, -1, "",
            style=wx.TE_MULTILINE | wx.TE_READONLY | wx.TE_LINEWRAP | wx.TE_WORDWRAP)
        self.__set_properties()
        self.__do_layout()
        self.Bind(wx.EVT_BUTTON, self.Go, self.button_1)

    def __set_properties(self):
        self.SetTitle("HTML text ratio")
        self.text_ctrl_1.SetMinSize((200, 25))
        self.text_ctrl_2.SetMinSize((200, 75))

    def __do_layout(self):
        grid_sizer_1 = wx.FlexGridSizer(2, 3, 5, 10)
        grid_sizer_1.Add(self.label_1, 0, wx.ALIGN_CENTER_HORIZONTAL | wx.ALIGN_CENTER_VERTICAL, 0)
        grid_sizer_1.Add(self.text_ctrl_1, 0, wx.EXPAND, 0)
        grid_sizer_1.Add(self.button_1, 0, 0, 0)
        grid_sizer_1.Add(self.dummy, 0, 0, 0)
        grid_sizer_1.Add(self.text_ctrl_2, 0, wx.EXPAND, 0)
        self.SetSizer(grid_sizer_1)
        grid_sizer_1.Fit(self)
        grid_sizer_1.AddGrowableCol(1)
        grid_sizer_1.AddGrowableRow(1)
        self.Layout()

    def Go(self, event):
        # Load the requested webpage and determine its length
        try:
            f = urllib.urlopen(self.text_ctrl_1.Value)
        except IOError:
            self.text_ctrl_2.Value = "Could not open url."
            return
        html = f.read(-1)
        f.close()
        html_length = len(html)
        # Extract the body
        soup = BeautifulSoup(html)
        body = soup.find("body").extract()
        # Remove scripts from the body
        for script in body.find_all("script"):
            script.extract()
        # Extract the text from the body and determine its length
        text = body.get_text(strip = False)
        text_length = len(text)
        # Calculate ratio
        if html_length != 0:
            ratio = text_length / html_length
        else:
            self.text_ctrl_2.Value  = "Length of retrieved html seems to be zero"
            return
        # Present the results
        self.text_ctrl_2.Value  = "Html length: {0:d} characters\n".format(html_length)
        self.text_ctrl_2.Value += "Text length: {0:d} characters\n".format(text_length)
        self.text_ctrl_2.Value += "Text html ratio: {:.0%}\n".format(ratio)
        event.Skip()

if __name__ == "__main__":
    app = wx.PySimpleApp(0)
    wx.InitAllImageHandlers()
    frame_1 = MainFrame(None, -1, "")
    app.SetTopWindow(frame_1)
    frame_1.Show()
    app.MainLoop()
