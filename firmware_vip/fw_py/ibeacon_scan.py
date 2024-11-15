import ubluetooth

class BLEScan:
    def __init__(self, found_cb):
        self.ble = ubluetooth.BLE()
        self.ble.active(True)
        self.target_uuid = bytes([0xA1, 0xC2, 0x3D, 0xE5, 0x99, 0xBF, 0x4E, 0xD8, 0xA3, 0x21, 0xF5, 0x49,0x7F, 0xA9, 0xCC, 0xB3])
        self.ble.irq(self.irq)
        self.found_cb = found_cb

    def irq(self, event, data):
        if event == 5:
            addr_type, addr, adv_type, rssi, adv_data = data
            self.parse_ibeacon(adv_data, rssi)

    def parse_ibeacon(self, adv_data, rssi):
        if len(adv_data) >= 23:
            uuid = bytes(adv_data[9:25])
            if uuid == self.target_uuid:
                if(self.found_cb):
                    self.found_cb(rssi)

    def scan(self, timeout=0):
        self.ble.gap_scan(timeout * 1000, 30000, 30000)
    
    def stop(self):
        self.ble.gap_scan(None)
    
    def deinit(self):
        self.ble.gap_scan(None)
        self.ble.active(False)
