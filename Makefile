# Henry Chen
# This make file creates the main program. It also cleans up any previous versions of that program.
# November 8 2022
export: bluetoothAttendence

bluetoothAttendence: BluetoothScanner.cpp DatabaseManager.cpp DeviceRegister.cpp Login.cpp Scanner.cpp SQLQuery.cpp UI.cpp
	g++ BluetoothScanner.cpp DatabaseManager.cpp DeviceRegister.cpp Login.cpp Scanner.cpp SQLQuery.cpp UI.cpp Attendance.cpp -lsqlite3 -o bluetoothAttendance

clean:
	rm bluetoothAttendence
	
