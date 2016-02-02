# Provide PWM values for left and right motors of a diff drive robot

# The range of [-128, 127] of the commands is mapped to
# max backward and forward speed via commanded PWM on
# the receiving controller.

int8 left_motor_cmd

int8 right_motor_cmd
