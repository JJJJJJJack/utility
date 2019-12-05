#!/bin/bash
# Run this before using the python class
Directory=$PWD
echo "Setting up environment variable for python"
echo "export PYTHONPATH=\"\$PYTHONPATH:$Directory\"" >> ~/.bashrc
