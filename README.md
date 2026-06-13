This project implements a fixed-size circular buffer (Ring Buffer) for uint8_t data with a capacity of 8 bytes. The implementation supports initialization, write, read, count, full-check, and empty-check operations. It demonstrates buffer wrap-around and proper handling of buffer full and buffer empty conditions without overwriting unread data.

Features:
Fixed buffer size of 8 bytes.

FIFO (First In First Out) operation.
Buffer initialization.
Single-byte write operation.
Single-byte read operation.
Buffer full detection.
Buffer empty detection
Current data count retrieval.
Wrap-around implementation using bitwise AND optimization.
