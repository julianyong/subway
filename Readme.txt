请按照E:\\subway\\subway\\Debug\\beijing-subway.txt的路径存储beijing-subway.txt
控制台参数说明：
	/l：输出线路上的所有站点	例如  /l 九号线
	/a：从某一点出发遍历全图	例如 /a 北京西站
	/b：输出两点之间的最短路径（换乘站额外加3）	例如 /b 魏公村 北京西站
	/z：测试文件内容是否满足：站点数正确，没有遗漏的站点，遍历次序合理		例如 /z E:\subway\subway\test.txt（要测试的目标文件的绝对路径）
	/g：显示图形界面
注意：/g /b的功能通过Subway.exe实现，存放在Subway中  /l /a /z的功能通过subway.exe实现存放在subway_中