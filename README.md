# OpenShow
OpenShow是一个Qt5.7实现的机器学习和深度学习应用的展示平台，可以通过连接服务器端(python3)完成相应的功能(因为深度学习普遍需要高配置的服务器)。目前应用包括人脸检测，人脸生成，人脸识别等。 
# Client
为了使OpenShow的Client具有良好的可扩展性和不同应用之间的低耦合性，我们利用了反射特性。当添加新的应用时，该应用需要继承AbstractWidget(继承自QWidget)，并且使用宏REGISTER_WIDGET_CLASS(类名)注册。  
而mainwindow主要维持两个控价，一个是QStackedWidget，另一个是QListWidget。QStackedWidget主要是把注册过的应用添加进来，而QListWidget是通过维持注册的应用的名称来切换不同的应用。 
# Server
类似的，服务器端也使用了反射特性。不同的应用服务器需要继承抽象类AbstractModel，该类只有一个抽象函数processData(input)。通过重载这个函数，不用的应用服务器通过接收客户端发过来的数据，返回相应的输出。不同的应用程序在server.py中通过processor字典进行注册。  
server.py主要是接收客户端的发送的数据，解析不同的应用类型，调用不同的应用服务器。

