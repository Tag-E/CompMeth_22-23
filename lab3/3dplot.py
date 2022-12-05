import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation

#I define the elementary steps i take in 3D 
#(to use choice i have to cheat: i add a 1 with 0 probability that will let the function work)
elem_steps = (1,(1.0,0.0,0.0), (1.0,0.0,0.0), (1.0,0.0,0.0), (1.0,0.0,0.0), (1.0,0.0,0.0), (0.0,-1.0,0.0), (0.0,0.0,1.0), (0.0,0.0,-1.0))
probSteps=[0.0,1/8.0,1/8.0,1/8.0,1/8.0,1/8.0,1/8.0,1/8.0,1/8.0]

Nsteps=10**2

steps = np.random.choice(elem_steps,Nsteps,p=probSteps)
path = np.asarray([i for i in steps],dtype=float).cumsum(axis=0)



fig = plt.figure() #new figure

maxSize = np.max(np.abs(path))

#figure general setup
ax = fig.add_subplot(111, projection='3d', autoscale_on=False, xlim=(-maxSize, maxSize), ylim=(-maxSize, maxSize), zlim=(-maxSize,maxSize))
ax.grid()
ax.set_xlabel("x(t) [m]")
ax.set_ylabel("y(t) [m]")
ax.set_zlabel("z(t) [m]")
plt.title("3D Random Walks")

#startup of animation

x = path[:,0]        #coordinates of rnd walks
y = path[:,1]
z = path[:,2]

tail, *_ = ax.plot3D(x[0],y[0],z[0], '.', color='red',alpha=0.2)
cursor, *_ = ax.plot3D([],[],[], 'o', color='blue')
info_template = 'step number = %.d '
info_text = ax.text(0.05,0.95,0.95,'', transform=ax.transAxes)

#function to update the plot
def update_plots(i):
    tailCond=True
    if tailCond:
        if i>10:
            #tail.set_data(x[i-10:i],y[i-10:i],z[i-10:i]) #we draw a vanishing tail behind the cursor
            tail.set_3d_propertie((x[i-10:i],y[i-10:i],z[i-10:i]))
            
        else: 
            #tail.set_data(x[:i],y[:i],z[:i])
            tail.set_3d_properties((x[:i],y[:i],z[:i]))
    else: 
         #tail.set_data([],[],[])
         tail.set_3d_properties([],[],[])
    #cursor.set_data(x[i],y[i],z[i])
    cursor.set_3d_properties((x[i],y[i],z[i]))
        
    #we update te step cpunter
    info_text.set_text(info_template % (i))
    # Return a tuple
    return tail, cursor, info_text

#animation of the plot
anim = animation.FuncAnimation(fig, update_plots, np.arange(1, path.shape[0]), interval=10, blit=True, repeat=True)

#we look at the gif
plt.show() 
