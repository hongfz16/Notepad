说明文档
===================

目标
-------------------
1. 不使用MFC文本框控件，实现一个简单的文本编辑器
2. 最低要求如下：
    * 带有图形界面
    * 能够比较方便的给不同的字符设置不同的字体、颜色和字号
    * 可以设置字与字之间的间距
3. 另外还实现了以下功能
    * 保存、打开自定义格式的文件
    * 设置对齐方式，包括左对齐、居中对齐、右对齐、分散对齐
    * 设置行间距

构件库
-------------------
详情请参见Class List

UI界面的交互实现方法说明
-------------------
1. 设置字体字号颜色 \
通过`CFontDialog`窗口类，创建选择字体的窗口 \
用户选择字体以及颜色后，获取字体信息`LOGFONT`以及颜色信息`REFCOLOR`\
通过`set_select_font`与`set_select_col`函数将字体以及颜色信息传递给后端
2. 设置字间距行间距 \
通过`M_PARA_DIA`对话框，获取用户设置的字间距与行间距的值 \
通过`set_select_lspace`与`set_select_cspace`函数将字间距与行间距传给后端
3. 保存、打开文件 \
通过`CFileDialog`类，返回用户需要保存或者打开文件的路径
通过`#`与`#`函数将路径作为字符串传给后端
4. 设置对齐方式 \
直接通过消息响应函数，调用`set_select_align`函数,设置对齐方式

后端（kernal）实现方法说明
-------------------

UI及交互部分遇到的问题及解决方案
-------------------
1. 绘图过程闪烁的问题 \
问题描述：使用过程中每当需要屏幕刷新的时候，画面会不停的闪烁 \
可能原因：每次调用OnPaint函数的时候都会先将屏幕清空，由于绘制屏幕仍然需要一定的时间，所以每次重绘都会出现闪烁的情况 \
解决方案：使用双缓冲绘图，分为两个部分：\
(1)重载`BOOL CChildView::OnEraseBkgnd(CDC* pDC)`函数，使得画面不会被擦除\
(2)先在使用内存DC上画图，画好后直接调用`BitBlt`函数将画面传给物理DC

2. 滚动条位置以及大小的问题\
问题描述：滚动条大小以及位置随着窗口大小改变而随机变动\
可能原因：由于滚动条控件需要手动设置大小以及位置，所以当改变窗口大小的时候会出现滚动条位置偏移的情况\
解决方案：设置两个变量：`m_client_cy`记录页面长度，`scrolledpix`记录页面相对于窗口上端的偏移量\
每次重绘的时候通过这两个量来重新计算滚动条的大小以及位置\

3. 解析用户传入的键盘消息\
问题描述：根据官方文档，键盘消息的对应关系很复杂，需要解析传入的参数才能获得字符信息\
解决方案：使用`void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)`的消息响应函数\
系统将键盘消息处理后返回用户输入的字符\

4. 连按消息的问题\
问题描述：通常连按一个按键，被认为是连续输入字符\
解决方案：在`void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) `函数中\
`nRepCnt`参数是用于标记连按消息的次数的，循环相应的次数即可实现连续输入\

5. 获取字体的像素大小的问题\
问题描述：`LOGFONT`结构体的成员`lfHeight`与`lfWidth`不是像素高度\
解决方案：通过公式`pixHeight = -(lfHeight * 72) / GetDeviceCaps(hDC,LOGPIXELSY)`转换为像素高度\
参考资料：[MSDN上关于LOGFONT的说明](https://msdn.microsoft.com/zh-cn/library/bb773327.aspx)

后端（kernal）遇到的问题及解决方案
-------------------

测试用例
-------------------

总结
-------------------
1. 程序具有一定的可使用性，实现了基本目标，在数据规模不太大的情况下可以达到较好效果
2. 当数据规模较大时（超过50000字符），会出现明显的卡顿现象，所以程序仍然有很大改进空间

作者信息
-------------------
* kernal部分作者：李仁杰
    * 学院：清华大学软件学院
    * 班级：软件62
    * 学号：
    * e-mail：
    * 电话：
* UI及交互部分作者：洪方舟
    * 学院：清华大学软件学院
    * 班级：软件62
    * 学号： 2016013259
    * e-mail: hongfz16@163.com
    * 电话：15062727188