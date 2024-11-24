Until recently, nearly every computer program that you might have interacted with during an ordinary day was coded up as a rigid set of rules specifying precisely how it should behave. Say that we wanted to write an application to manage an e-commerce platform. After huddling around a whiteboard for a few hours to ponder the problem, we might settle on the board strokes of a working solution, for example: (i) users interact with the application through an interface running in a web browser or mobile application; (ii) our application interacts with a commercial-grade database engine to keep track of each user's state and maintain records of historical transaction; and (iii) at the heart of our application, the business logic (you might say, the *brains*) of our application spells out a set of rules that map every conceivable circumstance to the corresponding action that our program should take.

直到最近，几乎所有你能见到的程序，都是平日里按照固定的规则编写出来的，它们精确地执行着自己本该完成的任务。比方说我们想要写一个应用来管理电商平台。在围绕着白板思考这个问题几小时后，我们可能会突然在板子上写出解决方案，例如：（1）用户用户通过网页浏览器或手机应用与我们的平台交互。（2）平台与商业级别的数据库保持交互，用于追踪每个用户的状态，并持续记录历史交易。以及（3）平台的核心：业务逻辑（也可以说是大脑），写出了对于每一种用户行为应该采取的行动。

To build the brains of our application, we might enumerate all the common events that our program should handle. For example, whenever a customer clicks to add an item to their shopping cart, our program should add an entry to the shopping cart database, associating that user's ID with the requested product's ID. What happens if a user initiates a purchase with an empty cart? While few developers ever get it completely right the first time (it might take some test runs to work out the kinks), for the most part we can write such programs and confidently launch them before ever seeing a real customer. Our ability to manually design automated systems that drive functioning products and systems, often in novel situations, is a remarkable cognitive feat. And when you area able to devise solutions that work 100% of the time, you typically should not be worrying about machine learning.

为了搭建平台的业务系统，我们可能会列举出程序应该处理的全部事件。比如说，当用户添加物品到他们的购物车时，我们的程序应该访问数据库，将商品ID与用户ID关联起来。用户在购物车为空时发起一次购买会发生什么？尽管只有少数开发者能在一开始就做出完备的程序（通常会在程序完成后对程序做一些测试，以发现问题），但大多数时候我们都能写出这样的程序，并在用户开始体验之前信心满满地启动它。我们能够设计出驱动产品和系统的自动化系统的能力（且常常是在全新的情况下实现），是一项令人惊叹的认知特征。且当你能设计出100%工作的解决方案时，你就不需要担心机器学习了。

Fortunately for the growing community of machine learning scientists, many tasks that we would like to automate do not bend so easily to human ingenuity. Imaging huddling around the whiteboard with the smartest minds you know, but this time you are tackling one of the following problems:

幸运的是，对于日益壮大的机器学习科学家群体来说，许多我们想要自动化的任务并未轻易受限于人类智慧。想象你和世界上最聪明的人一起围坐在白板周围，但这一次你需要面对以下问题：

- Write a program that predicts tomorrow's weather given geographic information, satellite images, and a trailing window of past weather.

- 写一个程序，基于地理信息、卫星图和过去的天气数据预测明天的天气。
- Write a program that takes in a factoid question, expressed in free-form text, and answers it correctly.
- 写一个程序，接收任意形式描述的抽象问题，然后正确回答这个问题。

- Write a program that, given an image, identifies every person depicted in it and draws outlines around each.
- 写一个程序，识别出一张图片中所有的人，并用线描绘出人物的外轮廓。
- Write a program that presents users with products that they are likely to enjoy but unlikely, in the natural course of browsing, to encounter.
- 写一个程序，向用户展示他们平日里不太可能浏览到，但可能会喜欢的商品。

For these problems, even elite programmers would struggle to code up solutions from scratch. The reasons can vary. Sometimes the program that we are looking for follows a pattern that changes over time, so there is no fixed right answer! In such cases, any successful solution must adapt gracefully to a changing world. At other times, the relationship (say between pixels, and abstract categories) may be too complicated, requiring thousands or millions of computations and following unknown principles. In the case of image recognition, the precise steps required to perform the task lie beyond our conscious understanding, even though our subconscious cognitive processes execute the task effortlessly.

对于上述问题，即使是最顶尖的程序员也会挣扎着从零开始搭建代码。而原因是多种多样的。有时我们寻找的程序遵循着随时间改变的模式，所以对于这些问题并没有固定的正确答案。在这种情况下，任何成功的解决方案都需要优雅地适应瞬息万变的世界。另一方面，事物之间的联系（比如像素和抽象的类别）可能过于复杂，着要求成千上万次的计算，且需要遵循未知的原则。在图像识别的例子中，执行相关任务所需要的准确步骤要求超出了我们的认知理解范围，即使我们的潜意识能够毫不费力的处理这些问题。

Machine learning is the study of algorithms that can learn from experience. As a machine learning algorithm accumulates more experience, typically in the form of observational data or interactions with an environment, its performance improves. Contrast this with our deterministic e-commerce platform, which follows the same business logic, no matter how much experience accrues, until the developers themselves learn and decide that it is time to update the software. In this book, we will teach you the fundamentals of machine learning, focusing in particular on *deep learning*, a powerful set of techniques driving innovations in areas as diverse as computer vision, natural language processing, healthcare, and genomics.

机器学习是一种学习过往经历的学习算法。机器学习算法的表现随经验积累而提升，通常是增加观测数据或与环境交互。对比我们有着固定业务逻辑的电商平台，不管积累多少经验，只有到开发者自身认知并决定是时候升级软件时，电商平台的表现才会有提升。在本书中，我们会传授你机器学习的基础，特别会关注于“深度学习”这个功能强大的机器学习的子集，其在诸多领域如“计算机视觉”、“自然语言处理”、“医疗保健服务”和“基因学”上掀起了技术革命。