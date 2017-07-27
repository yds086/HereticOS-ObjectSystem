# HereticOS-ObjectSystem

HereticOS-ObjectSystem是一款C++语言开发的windows平台的轻量级分布式对象系统，使用代码生成器做对象序列化代码生成，对象序列化后可以存储到key value模式的对象服务器中，对象服务器为不同业务程序做对象共享与持久化，是一种敏捷开发利器。

代码目录说明
other\  序列化库目录
other\ObjectSystem                ObjectSystem第一版 
other\ObjectSystem2               ObjectSystem第二版
Example\CodeRender                对象序列化代码生成器
Example\ObjectSystemComServer     第一版ObjectSystem的MSSOAP对象服务器
Example\project_WhiteBoxStudio    第一版ObjectSystem框架基础上设计的一款软件，体现敏捷开发的思路。
Example\XMLObjectTest1            c++对象序列化例子
Example\ObjectSystem2Test         ObjectSystem第二版测试例子，以及一款击鼓传花的例子。


第一版ObjectSystem介绍

第一版实做了C++对象序列化，以及对象服务器的基本功能UpdataObject GetObject以及对象锁等，系统在设计时使用KV查询模式，如果需要在不同组件中同步对象，则需要应用自行在KV上设计邮箱，并自行轮询，多组件对相同对象写时需要对对象上锁，以防止对象被不同角色篡改。
第一版传输层使用MSSOAP来实现。

第二版ObjectSystem介绍
第二版在第一版基础上使用C++11中的lambda闭包技术实现了异步事件机制，因此增加消息推送能力，从而实现了基于KV模型的发布订阅模式，业务可以注册关注指定对象的UpdataObject NeedObject等事件，由于项目需要第二版ObjectSystem做了不部分重构，暂时去掉了MSSOAP传输层，实做了UDP传输层，未来可能会支持Win10 UWP等。

ObjectSystem2Test 击鼓传花例子介绍

//
//1. 发布订阅传递模式  适合需要及时更新业务数据的场合
//   该模式下所有Client注册关注自己花朵槽Updata事件。
//	 管理者放置花朵给一个指定Client的花朵槽时，该Client收到Updata事件，取出花朵等待若干秒后将花朵放入环上下一个用户的花朵槽，下一个用户循环此步骤
//
//2. 轮询更新传递模式  适合不需要随时跟新业务数据场合
//   该模式下所有Client不关注花朵槽事件。
//   所有没有拥有花的Client 定期查询环上上一个用户的花朵槽，如果拥有花朵则取出放入自己的花朵槽。
//   Client收到自己花朵槽Updata事件则说明拥有了花朵。
//
//3  管理员公共事件
//   所有Client注册接受管理员邮箱中全局信息对象的Updata事件，管理员Updata设置该对象时广播给所有客户端。
//   比如全局通知，启动关闭暂停，发送广告，重置等。
//   管理员负责初始化用户花朵槽和环,并提供NeedNewSlot服务接口为登陆用户分配一个花朵槽。
//
//4	 公告牌广播
//   所有游戏用户关注公告牌，其中用户传递等待时间是管理员动态设置。
//

ObjectSystem V2使用说明
ObjectSystem2Test设计用例：
1. 设计业务数据对象 RotationalFlowersDataMode.h
2. 编辑CodeRender\结构体序列化1.1\1.txt脚本，配置好指定代码生成器脚本（MakeTransportProtocol.mk），业务头文件目录（RotationalFlowersDataMode.h），代码输出目录（AppProtocol）等。
3. 将1.txt拷贝到d:\1.txt
4. 运行CodeRender，点测试按钮，代码生成好会在AppProtocol目录中
5. 将AppProtocol目录中所有文件加入到VS项目中。
6. 编写业务逻辑RotationalFlowers.h


CodeRender 原理以及使用介绍
CodeRender是学生时代的一个玩具，主要做自定义语法文法的模式提取变换，当时网上找到一个C语言编译器的例子用了它的词法分析器然后改了改，上层用借鉴专家系统模式识别的思想做了AST语义树生成，有了AST语义树，同样再用专家系统对AST树做模式识别变换到自己设计的予以模式。
该代码生成器之前做过COM代码HOOK 按照需要做一层Wrap,从而完成一些枯燥的代码编写工作，减少错误。
现在用于对象序列化代码生成。

语义分析语法，实例可以参看CodeRender\结构体序列化1.1\structtree.mk

语言解析表达式规范
+  连接两个规则表达式名称，表示两个规则名指定的表达式按照先后顺序必须都匹配成功（形成多个代码对象）
|	 连接两个规则表达式名称，表示两个规则名指定的表达式只要有一个匹配成功则该表达式成功(只针对当前的一个代码对象)
=  包表达式声明定义
N<规则表达式名> 表示指定的规则表达式要做N次匹配,直到当前包结束 无匹配返回状态将结果加入链
包<包起始规则表达式,包终止规则表达式,规则表达式名> 指定一个包的解析匹配规则
xxx<yyy>	表示一个语法匹配规则表达式名和表达式类型名 如 函数声明1<函数声明>=返回类型1+调用约定|NULL
NULL<规则表达式名> 表示表达式匹配失败也可返回成功（将填充默认值）
NULL_TRUE 特殊表达式，直接返回表达式匹配成功 用于解析预留接口
NULL_FALSE 特殊表达式，直接返回表达式匹配失败 用于解析预留接口
xxx(yyy)	表示一个词法匹配规则表达式名和表达式类型名 如 句尾1(句尾)=; 词内置类型匹配名有 词型，符号型，整型，浮点型，字符串型,字符型 暂时合并到表达式
ROOT<表达式名> 表示语义解析根入口
G(xxx)	表示一个表达式 G(表达式名1|表达式名2)	暂时不支持
WORD(xxx)	表匹配一个词 比如WORD(;)
 

代码生成表达式定义，实例可参看 CodeRender\结构体序列化1.1\结构预处理MAKE.mk

表达式为真，则代码返回给上层表达式
MAKE_N<代码节点,第一个代码节点MAKE,中间的过程代码节点MAKE,末尾的代码节点MAKE> 穷举所有符合代码节点表达式的代码节点，然后交由后面的MAKE表达式处理
MAKE_ONE<代码节点,代码节点MAKE> 只MAKE处理第一个符合代码节点表达式的代码节点 
MAKE_ADD<MAKE表达式字符串的表达式名称>	添加或者设置一条表达式
WORD(x) 返回字符串，如果字符串中有"则需要在前面加\
NOT<MAKE表达式> 如果MAKE表达式成功则返回假，用于条件控制执行，并将MAKE表达式的结果抛弃不加入结果链
IF<MAKE表达式> 如果MAKE表达式成功则返回真，用于条件控制执行，并将MAKE表达式的结果抛弃不加入结果链
DEBUGOUT<"字符串">	打印字符串
DEBUGOUT<MAKE表达式> 打印MAKE表达式生成的结果，并影响参与计算的表达式真假状态
MAKE_TO<MAKE表达式,保存目标对象名> 如果MAKE表达式为真则将其结果保存到目标对象名指定的对象中去
MAKE_MAKECODE<需要解析处理的源对象,处理源对象的脚本对象>  对象可以是一个MAKE表达式返回的字符串，也可以直接是一个对象字符串如文件路径
MAKE_CODE_TO<源对象,处理源对象的MAKE表达式,输出对象> 对象可以是文件路径字符串或者是一个MAKE表达式结果,处理源对象的MAKE表达式 对 源对象分析处理后的结果存入 输出对象
MAKE_BIND_ROUTING<被绑定的虚路径名字符串,需要映射到虚路径的真实路径字符串>
+  表达式结果连接并流程控制 A+B 如果A为真则执行B，AB都为真则返回真
&  表达式结果连接并流程控制 A&B 不管A执行是否成功，都需执行B, AB只要有一个为真则返回真
#  表达式结果连接并流程控制 A#B 与+意义相同只是返回的结果不是用句连接，而是词的融合
|  表达式结果连接并流程控制 A|B	如果A为真，则不执行B，跳过B执行下一个表达式，如果A为假，则执行B,返回结果为A或B,返回的代码是真值的那个表达式MAKE结果
