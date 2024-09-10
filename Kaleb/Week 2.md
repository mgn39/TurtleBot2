9/10/24
### Sensor research
- **IMU (Inertial Measurement Unit):** An IMU can measure angular velocities and accelerations, which can be used to determine orientation. For azimuth, a 9-axis IMU (which includes gyroscope, accelerometer, and magnetometer) would be ideal. The magnetometer helps in determining the heading relative to the Earth's magnetic field.
- **Compass Module:** A digital compass or magnetometer, like the HMC5883L or QMC5883L, can provide direct azimuth measurements. These sensors can give you the heading relative to the magnetic north.
- **GPS and SLAM:** If you need more precise positioning and azimuth information, combining GPS data with SLAM (Simultaneous Localization and Mapping) can be effective. SLAM algorithms can help in determining the robot's orientation in a mapped environment.
- **Using ROS (Robot Operating System):** In ROS, you can integrate various sensors and use packages like `robot_localization` to fuse data from IMUs, compasses, and GPS for accurate azimuth and orientation information.

### Robot arm
- Designs