Patompak, Chong | International Journal of Social Robotics | May 25th, 2019

**Link:** [Learning Proxemics](https://link.springer.com/article/10.1007/s12369-019-00560-9)

**Conclusion:**

They propose a new robot navigation strategy to socially interact with people reflecting upon the social relationship between the robot and each person. The social force model (SFM) is designed by a fuzzy inference system, where the membership function are optimized to give the robot the ability to navigate autonomously in the quality interaction area using a reinforcement learning algorithm.

Need a clear definition of interaction areas:
- Quality interaction area where people can be engaged in high-quality interaction with robots
- Private area not be interfered with by the robot speech or action

People feel safe and comfortable within their own territory they keep from others. For mobile robot navigation in a human populated environment, collision avoidance is one of the most important concerns. The estimated SFM is used as a cost map for the path planner to generate robot navigation paths to make people feel comfortable.

There are 3 mains parts in the proposed method:
- Human social model designed by an Asymmetric Gaussian function with is parameters are determine from a fuzzy inference system (FIS)
- Reinforcement learning which used as a tool to update the parameters of the FIS
- Social path planner to generate socially competent navigation using the human social model.

The output from the fuzzy inference system is the parameters to calculate the model of privacy area of the human which can be calculated by the Gaussian function. Based on preliminary human's private area, the robot can estimate the social map that includes people's private area and use it to generate its navigation paths to perform social interaction.

The reinforcement learning method is used to learn from human feedback how to spot and respect the private area varying from one person to another. They use Transition based Rapidly-Exploring Random Tree (T-RRT) that can choose an optimal navigation path in the social cost map and collect the reward. This planner produces the path that efficiently follows the low-cost area and the saddle point of the cost map. use T-RRT for the exploration and optimal path generation, allowing the robot to evaluate the navigation cost as the social map is updated.

A new proxemics learning strategy was proposed for social mobile robots toward realizing socially competent navigation behaviors by integrating a fuzzy inference system and a reinforcement learning method.