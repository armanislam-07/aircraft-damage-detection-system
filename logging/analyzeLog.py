import matplotlib.pyplot as plt
import pandas as pd 
import tkinter as tk
from tkinter import filedialog
import os

root = tk.Tk()
root.withdraw()

file_path = filedialog.askopenfilename(
    title="Select a File",
    filetypes=[("All Files", "*.*"), ("Text Files", "*.txt")]
)

file_name, ext = os.path.splitext(file_path) # we don't need the ext (look to change this to make it cleaner) 


df = pd.read_csv(file_path)
timeMS = df.iloc[:,0]
resistance = df.iloc[:,1]
voltage = df.iloc[:,2] 
current = df.iloc[:,3] 
time = timeMS / 1000







if __name__ == "__main__":
    plt.figure(1)
    plt.plot(time, resistance)
    plt.xlabel('Time (s)')
    plt.ylabel('Resistance (Ohms)')
    plt.title('Resistance vs Time of UAV flight test')
    plt.savefig(f"{file_name}.png")
    # Save the png in a folder img/, so we can high quality images 
    plt.show()


