
;====loader.sys 短项
db "loader.sys"
db 0x25 ;Archive SystemFile ReadOnly
db 0x00 ;REV
db 0x00
db 0000000000000000b ;00:00:00 CreateTime
db 0000000000010001b ;1980/1/1 CreateDate
db 0000000000010001b ;1980/1/1 AccDate
db 0x00 ;簇号0x0005高
db 0000000000000000b ;00:00:00 WriteTime
db 0000000000010001b ;1980/1/1 WriteDate
db 0x05 ;簇号0x0005低
dd 0x00007fff ; 32767byte 32Kb
