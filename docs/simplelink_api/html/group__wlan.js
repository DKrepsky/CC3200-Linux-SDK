var group__wlan =
[
    [ "slSmartConfigStartAsyncResponse_t", "structsl_smart_config_start_async_response__t.html", [
      [ "private_token", "structsl_smart_config_start_async_response__t.html#ae788e671c21e21c7913ac4b439887785", null ],
      [ "private_token_len", "structsl_smart_config_start_async_response__t.html#aac6bab1ba54c9d01c548a5971fe18a95", null ],
      [ "ssid", "structsl_smart_config_start_async_response__t.html#aaf9ed7d9e9d6c2bdd7b7fc7b768b81de", null ],
      [ "ssid_len", "structsl_smart_config_start_async_response__t.html#a4fd951e04acb1b6941b85533d248ba27", null ],
      [ "status", "structsl_smart_config_start_async_response__t.html#a9bd457bdee1c8059b6cf88ac0647d0e1", null ]
    ] ],
    [ "slSmartConfigStopAsyncResponse_t", "structsl_smart_config_stop_async_response__t.html", [
      [ "padding", "structsl_smart_config_stop_async_response__t.html#aee74651e918d4c23f3eabe25fbbf8142", null ],
      [ "status", "structsl_smart_config_stop_async_response__t.html#a0fcf01673166445f62de27571ae41090", null ]
    ] ],
    [ "slWlanConnFailureAsyncResponse_t", "structsl_wlan_conn_failure_async_response__t.html", [
      [ "padding", "structsl_wlan_conn_failure_async_response__t.html#aee74651e918d4c23f3eabe25fbbf8142", null ],
      [ "status", "structsl_wlan_conn_failure_async_response__t.html#a0fcf01673166445f62de27571ae41090", null ]
    ] ],
    [ "slWlanConnectAsyncResponse_t", "structsl_wlan_connect_async_response__t.html", [
      [ "bssid", "structsl_wlan_connect_async_response__t.html#a26584d70e5f1888864c8c3f3d43e21c7", null ],
      [ "connection_type", "structsl_wlan_connect_async_response__t.html#a02de4ebfc0ae3ef0524521fea6cdba7a", null ],
      [ "go_peer_device_name", "structsl_wlan_connect_async_response__t.html#a134cf4c828e548efdc5febe2b8b826ae", null ],
      [ "go_peer_device_name_len", "structsl_wlan_connect_async_response__t.html#ad58b0d3c676c06221fa491ec4b384cad", null ],
      [ "padding", "structsl_wlan_connect_async_response__t.html#a591a340cf7a3bc8395dc554fc01910b7", null ],
      [ "reason_code", "structsl_wlan_connect_async_response__t.html#aef3e37e4643200170981d36287a9bbf5", null ],
      [ "ssid_len", "structsl_wlan_connect_async_response__t.html#a2e45fb530d9c89d3673ea6e05f07844d", null ],
      [ "ssid_name", "structsl_wlan_connect_async_response__t.html#a89e1ad338d707b4182bd0a8bf5a15bc6", null ]
    ] ],
    [ "slPeerInfoAsyncResponse_t", "structsl_peer_info_async_response__t.html", [
      [ "go_peer_device_name", "structsl_peer_info_async_response__t.html#a134cf4c828e548efdc5febe2b8b826ae", null ],
      [ "go_peer_device_name_len", "structsl_peer_info_async_response__t.html#ad58b0d3c676c06221fa491ec4b384cad", null ],
      [ "mac", "structsl_peer_info_async_response__t.html#a51fa48efb76fa1995446db52ac06a46f", null ],
      [ "own_ssid", "structsl_peer_info_async_response__t.html#af3d92d2c6ec560caf5c705fa487d9622", null ],
      [ "own_ssid_len", "structsl_peer_info_async_response__t.html#a8e4b7daa24f45b8112386655cc2c5c61", null ],
      [ "padding", "structsl_peer_info_async_response__t.html#a46d3c053c50ca746d761db91f590bb60", null ],
      [ "wps_dev_password_id", "structsl_peer_info_async_response__t.html#a3b1181843fd7fc28edccb34fe78934cc", null ]
    ] ],
    [ "SlWlanEventData_u", "union_sl_wlan_event_data__u.html", [
      [ "APModeStaConnected", "union_sl_wlan_event_data__u.html#a8a4b774d3fea5bd36d46e36326f11ed4", null ],
      [ "APModestaDisconnected", "union_sl_wlan_event_data__u.html#a5e285baad857f73a0167f73e4b17ae50", null ],
      [ "P2PModeDevFound", "union_sl_wlan_event_data__u.html#a8b490ba7a54396f6e289b5789644de5f", null ],
      [ "P2PModeNegReqReceived", "union_sl_wlan_event_data__u.html#aee4d526e0489f6384555d71c6a4c2ff3", null ],
      [ "P2PModewlanConnectionFailure", "union_sl_wlan_event_data__u.html#a2211e22e568ee4349eebd7ed5b6f9b60", null ],
      [ "smartConfigStartResponse", "union_sl_wlan_event_data__u.html#a3e0a9eb580163ca72c178d96a5edba79", null ],
      [ "smartConfigStopResponse", "union_sl_wlan_event_data__u.html#a962b4e0845dd71daaf9929aea34183fc", null ],
      [ "STAandP2PModeDisconnected", "union_sl_wlan_event_data__u.html#abf61e2e1e81c5eda10f6ff84a7197b31", null ],
      [ "STAandP2PModeWlanConnected", "union_sl_wlan_event_data__u.html#a406b4e8670796f9cdc1746646fab6588", null ]
    ] ],
    [ "SlWlanEvent_t", "struct_sl_wlan_event__t.html", [
      [ "Event", "struct_sl_wlan_event__t.html#adeedbaaa252b969fc66e151eef37ea62", null ],
      [ "EventData", "struct_sl_wlan_event__t.html#ae587c51197255d4e4ef20cc90d73825f", null ]
    ] ],
    [ "SlGetRxStatResponse_t", "struct_sl_get_rx_stat_response__t.html", [
      [ "AvarageDataCtrlRssi", "struct_sl_get_rx_stat_response__t.html#af3660978617c803a996f041215004a50", null ],
      [ "AvarageMgMntRssi", "struct_sl_get_rx_stat_response__t.html#a2050deb55011de7a472c8d5bcd6099f7", null ],
      [ "GetTimeStamp", "struct_sl_get_rx_stat_response__t.html#a85c0324d0b3de70a327e185173309a5c", null ],
      [ "RateHistogram", "struct_sl_get_rx_stat_response__t.html#ad18c6011a86553bd786ffae0f7b87538", null ],
      [ "ReceivedAddressMismatchPacketsNumber", "struct_sl_get_rx_stat_response__t.html#a006a7c484f312ebb8a96587d24cc0686", null ],
      [ "ReceivedFcsErrorPacketsNumber", "struct_sl_get_rx_stat_response__t.html#a6e06f9a2b719028a084d2fc2333cd309", null ],
      [ "ReceivedValidPacketsNumber", "struct_sl_get_rx_stat_response__t.html#a0b84e628b2501fbf4a814b2f678a63ef", null ],
      [ "RssiHistogram", "struct_sl_get_rx_stat_response__t.html#a11b977458ccb1ceade91d3f2ae733307", null ],
      [ "StartTimeStamp", "struct_sl_get_rx_stat_response__t.html#ac40e3ad339a01bee80c412d99eb1a128", null ]
    ] ],
    [ "Sl_WlanNetworkEntry_t", "struct_sl___wlan_network_entry__t.html", [
      [ "bssid", "struct_sl___wlan_network_entry__t.html#a1625b9ac8d0d51aa89df83295c9a5de2", null ],
      [ "reserved", "struct_sl___wlan_network_entry__t.html#aa1d4d52e9a684f2a28c9c8b89573af18", null ],
      [ "rssi", "struct_sl___wlan_network_entry__t.html#a80c3df13ed7cf0b1a5e5639811c82f34", null ],
      [ "sec_type", "struct_sl___wlan_network_entry__t.html#af791c098aa0b08d0ee0126843b1fe855", null ],
      [ "ssid", "struct_sl___wlan_network_entry__t.html#ad097bad1e9bb0c4e70de8748263b76da", null ],
      [ "ssid_len", "struct_sl___wlan_network_entry__t.html#a2e45fb530d9c89d3673ea6e05f07844d", null ]
    ] ],
    [ "SlSecParams_t", "struct_sl_sec_params__t.html", [
      [ "Key", "struct_sl_sec_params__t.html#af943e0f6d7ca78a5b795c8da294c5d1e", null ],
      [ "KeyLen", "struct_sl_sec_params__t.html#a9b049837934488d32481cf8d616e12af", null ],
      [ "Type", "struct_sl_sec_params__t.html#a1d58ad89ed5b340d15c354b769f8ecc2", null ]
    ] ],
    [ "SlSecParamsExt_t", "struct_sl_sec_params_ext__t.html", [
      [ "AnonUser", "struct_sl_sec_params_ext__t.html#a882de2171333187a5cded2550accce18", null ],
      [ "AnonUserLen", "struct_sl_sec_params_ext__t.html#ac62b273b2e1b1c60eca7ef61a29b0aa5", null ],
      [ "CertIndex", "struct_sl_sec_params_ext__t.html#a55a132bbb3126099cb8f12cb6d174876", null ],
      [ "EapMethod", "struct_sl_sec_params_ext__t.html#a4f18f173d08eff5ae05fa940c60df4c0", null ],
      [ "User", "struct_sl_sec_params_ext__t.html#afc4f533307e2aee2c6c114f8941aa499", null ],
      [ "UserLen", "struct_sl_sec_params_ext__t.html#a24af689142eda26860754c5e9c0f9e60", null ]
    ] ],
    [ "SlGetSecParamsExt_t", "struct_sl_get_sec_params_ext__t.html", [
      [ "AnonUser", "struct_sl_get_sec_params_ext__t.html#a402a97b0e8257ae2f2b928c7590d0b03", null ],
      [ "AnonUserLen", "struct_sl_get_sec_params_ext__t.html#ac62b273b2e1b1c60eca7ef61a29b0aa5", null ],
      [ "CertIndex", "struct_sl_get_sec_params_ext__t.html#a55a132bbb3126099cb8f12cb6d174876", null ],
      [ "EapMethod", "struct_sl_get_sec_params_ext__t.html#a4f18f173d08eff5ae05fa940c60df4c0", null ],
      [ "User", "struct_sl_get_sec_params_ext__t.html#ac3b3c772e1d98758cc674e2f6f0658d5", null ],
      [ "UserLen", "struct_sl_get_sec_params_ext__t.html#a24af689142eda26860754c5e9c0f9e60", null ]
    ] ],
    [ "slWlanScanParamCommand_t", "structsl_wlan_scan_param_command__t.html", [
      [ "G_Channels_mask", "structsl_wlan_scan_param_command__t.html#a1401545f73ec1aeb0f1caff176a49877", null ],
      [ "rssiThershold", "structsl_wlan_scan_param_command__t.html#a12b902a2708b47b806a727a2604f9c4f", null ]
    ] ],
    [ "sl_protocol_InfoElement_t", "structsl__protocol___info_element__t.html", [
      [ "data", "structsl__protocol___info_element__t.html#a27e0ca8e8af28ff69c2df264599f5625", null ],
      [ "id", "structsl__protocol___info_element__t.html#a2888afcbf466934238f060ea0b8300ed", null ],
      [ "length", "structsl__protocol___info_element__t.html#a128a630f6d2121a0106add0f03f1cab9", null ],
      [ "oui", "structsl__protocol___info_element__t.html#aa7158dccffcbe48160a5c4ac033466ff", null ]
    ] ],
    [ "sl_protocol_WlanSetInfoElement_t", "structsl__protocol___wlan_set_info_element__t.html", [
      [ "ie", "structsl__protocol___wlan_set_info_element__t.html#ac1029492d0e3b06663e3dfa879773e2a", null ],
      [ "index", "structsl__protocol___wlan_set_info_element__t.html#a1b7d00023fd5674c4bd44bc179294390", null ],
      [ "role", "structsl__protocol___wlan_set_info_element__t.html#a838542fa5c0baf0d55b638d8906ec18e", null ]
    ] ],
    [ "sl_WlanConnect", "group__wlan.html#ga15d4779e6097f67111c69eaaff56a261", null ],
    [ "sl_WlanDisconnect", "group__wlan.html#ga8d3140cea09851de2c580c89f222f808", null ],
    [ "sl_WlanGet", "group__wlan.html#gae085496a64690e1d90de834ec571a409", null ],
    [ "sl_WlanGetNetworkList", "group__wlan.html#ga620559124e4421c6887ec67ff50bbbbc", null ],
    [ "sl_WlanPolicyGet", "group__wlan.html#gab3fe766dab62ecd42836529be4c0b2e1", null ],
    [ "sl_WlanPolicySet", "group__wlan.html#gaa0491d6453e037c857bd10e3be87df3d", null ],
    [ "sl_WlanProfileAdd", "group__wlan.html#ga27081ec6f3047e97b8b024ae751c955b", null ],
    [ "sl_WlanProfileDel", "group__wlan.html#gac4bc2e3a0c2152b49a1614b08ee36204", null ],
    [ "sl_WlanProfileGet", "group__wlan.html#ga5195b07e98404f074e0294276fc64858", null ],
    [ "sl_WlanRxFilterAdd", "group__wlan.html#ga0f61489aecc77c79f5350a8c6bab3ab5", null ],
    [ "sl_WlanRxFilterGet", "group__wlan.html#gab5ffd26ae9abe6ea5bc61b99a0ced94f", null ],
    [ "sl_WlanRxFilterSet", "group__wlan.html#gac30d8b0d601562d2f8a8468da18bad11", null ],
    [ "sl_WlanRxStatGet", "group__wlan.html#gae42178af250ac0d4356459f666831ad1", null ],
    [ "sl_WlanRxStatStart", "group__wlan.html#ga40fdb95f2590b43c91a60377349aad4c", null ],
    [ "sl_WlanRxStatStop", "group__wlan.html#ga69b1778b120c0b2db7f2fd2884dde5d8", null ],
    [ "sl_WlanSet", "group__wlan.html#gab8ba00f95398b5dccd80550ab3fc17e5", null ],
    [ "sl_WlanSetMode", "group__wlan.html#ga14a7b9540cb77fd6f25d867dc4b86216", null ],
    [ "sl_WlanSmartConfigStart", "group__wlan.html#ga2ac29ca184173a50d76a36f259a4435d", null ],
    [ "sl_WlanSmartConfigStop", "group__wlan.html#gac95a8b72fab78924ea6b52e3799c7de6", null ]
];