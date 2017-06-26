import os, sys

os.sys.path.append('../dynamixel_functions_py')

import dynamixel_functions as dynamixel


ADDR_MX_TORQUE_ENABLE = 24
ADDR_MX_GOAL_POSITION = 30
ADDR_MX_PRESENT_POS = 36

PROTOCOL = 1

DXL_ID = 5 # Change based on motor id

BAUDRATE = 1000000  # Figure out baudrate (found default value from site)

DEVICENAME = "/dev/ttyUSB0".encode('utf-8')

TORQUE_ENABLE = 1
TORQUE_DISABLE = 0

DXL_MIN_POS = 400 # Find min pos
DXL_MAX_POS = 157 # Find max pos

DXL_MOVING_STATUS_THRESHOLD = 10 # find it

COMM_SUCCESS = 0
COMM_TX_FAIL = -1001

port_num = dynamixel.portHandler(DEVICENAME)
 
dynamixel.packetHandler()

index = 1
dxl_comm_result = COMM_TX_FAIL
dxl_goal_position = [DXL_MIN_POS, DXL_MAX_POS]

dxl_error = 0
dxl_present_pos = 0

if dynamixel.openPort(port_num):
	print("Succeeded opening port!")
else:
	print("Failed to open port!")
	quit()

if dynamixel.setBaudRate(port_num, BAUDRATE):
	print("Succeeded changing baudrate!")
else:
	print("Failed to change baudrate!")
	quit()

dxl_model_num = dynamixel.pingGetModelNum(port_num, PROTOCOL, DXL_ID)
if dynamixel.getLastTxRxResult(port_num, PROTOCOL) != COMM_SUCCESS:
	dynamixel.printTxRxResult(PROTOCOL, dynamixel.getLastTxRxResult(port_num, PROTOCOL))
elif dynamixel.getLastRxPacketError(port_num, PROTOCOL) != 0:
	dynamixel.printRxPacketError(PROTOCOL, dynamixel.getLastPacketError(port_num, PROTOCOL))
print((dxl_model_num)) 

dynamixel.write1ByteTxRx(port_num, PROTOCOL, DXL_ID, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE)
if dynamixel.getLastTxRxResult(port_num, PROTOCOL) != COMM_SUCCESS:
	dynamixel.printTxRxResult(PROTOCOL, dynamixel.getLastTxRxResult(port_num, PROTOCOL))
elif dynamixel.getLastRxPacketError(port_num, PROTOCOL) != 0:
	dynamixel.printRxPacketError(PROTOCOL, dynamixel.getLastPacketError(port_num, PROTOCOL))
else:
	print("Dynamixel has been successfully connected!")


dynamixel.write2ByteTxRx(port_num, PROTOCOL, DXL_ID, ADDR_MX_GOAL_POSITION, dxl_goal_position[index])
if dynamixel.getLastTxRxResult(port_num, PROTOCOL) != COMM_SUCCESS:
	dynamixel.printTxRxResult(PROTOCOL, dynamixel.getLastTxRxResult(port_num, PROTOCOL))
elif dynamixel.getLastRxPacketError(port_num, PROTOCOL) != 0:
	dynamixel.printRxPacketError(PROTOCOL, dynamixel.getLastRxPacketError(port_num, PROTOCOL))

while 1:
	dxl_present_pos = dynamixel.read2ByteTxRx(port_num, PROTOCOL, DXL_ID, ADDR_MX_PRESENT_POS)
	if dynamixel.getLastTxRxResult(port_num, PROTOCOL) != COMM_SUCCESS:
		dynamixel.printTxRxResult(PROTOCOL, dynamixel.getLastTxRxResult(port_num, PROTOCOL))
	elif dynamixel.getLastRxPacketError(port_num, PROTOCOL) != 0:
		dynamixel.getRxPacketError(PROTOCOL, dynamixel.getLastRxPacketError(port_num, PROTOCOL))
	
	print("[ID:%03d] GoalPos:%03d PresPos:%03d" % (DXL_ID, dxl_goal_position[index], dxl_present_pos))
	
	if not abs(dxl_goal_position[index] - dxl_present_pos) > DXL_MOVING_STATUS_THRESHOLD:
		break


dynamixel.write1ByteTxRx(port_num, PROTOCOL, DXL_ID, ADDR_MX_TORQUE_ENABLE, TORQUE_DISABLE)
if dynamixel.getLastTxRxResult(port_num, PROTOCOL) != COMM_SUCCESS:
	dynamixel.printTxRxResult(PROTOCOL, dynamixel.getLastTxRxResult(port_num, PROTOCOL))
elif dynamixel.getLastRxPacketError(port_num, PROTOCOL) != 0:
	dynamixel.printRxPacketError(PROTOCOL, dynamixel.getLastRxPacketError(port_num, PROTOCOL))

dynamixel.closePort(port_num)

