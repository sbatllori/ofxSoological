import numpy as np 
import os
import copy
import shutil
import argparse


def main():
 
    parser = argparse.ArgumentParser(description="Copies the files from a folder in reverse order with sequential names.")
    parser.add_argument("-f", "--frames_folder", type=str, required=True, help="Path to the folder where to find the frames to duplicate.")
    parser.add_argument("-z", "--zeroes", type=int, required=False, default=8, help="Number of zeroes (digits) of the sequential id in the file names.")
    args = parser.parse_args()

    folder_path = args.frames_folder
    len_number = args.zeroes

    print(f"[SOO INFO] Reading frames from {folder_path} with {len_number} digits expected on the sequential id.")

    # Load file names
    images = np.sort(os.listdir(folder_path))
    assert images[0][:-4] == "f" + len_number * "0", f"First sequential id needs to be {len_number} zeroes."

    # Define reference file names (existing files with reversed order)
    ref_file_names = np.flip(images)

    # Define new file names (follow the sequence)
    ext = images[0][-4:]
    num_images = len(images)
    num_digits = len(str(num_images))
    num_zeroes = len_number - num_digits
    new_file_names = ["f" + num_zeroes * "0" + str(num_images + x) + ext for x in range(num_images)]

    # Copie the files
    for i in range(len(new_file_names)):
        ref_path = os.path.join(folder_path, ref_file_names[i])
        new_path = os.path.join(folder_path, new_file_names[i])
        shutil.copy(ref_path, new_path)

    print(f"[SOO INFO] Copied {len(new_file_names)} images.")


if __name__ == '__main__':
    main()