// clothname.c  

#include <ansi.h>

string *com_type = ({
"�İ�"NOR, "����"NOR, "խ��"NOR, "����"NOR, "����"NOR, "�ް�"NOR, "����"NOR, 
"����"NOR, "С��"NOR,
});
string *man_color = ({
CYN"��", BLU"��", WHT"��", HIB"����", GRN"����", HIR"糺�", 
BLK"��", WHT"�ذ�", HIM"��", MAG"ǳ��", 
});
string *com_material = ({
"��", "��", "ӡ��", "��", "�鲼", "�ֲ�", 
});        
string *high_type = ({
"����"NOR, "��"NOR, "����"NOR, "����"NOR, "�İ�"NOR, "����"NOR, "����"NOR, 
"���"NOR, "����"NOR,
});
string *high_material = ({
"����", "��", "��", "����", "ֱ��", 
});                
string *wo_type = ({
"ȹ"NOR, "��ȹ"NOR, "��"NOR, "����"NOR, "С��"NOR, "��ȹ"NOR, "����"NOR,
});
string *wo_color = ({
RED"���", RED"����", HIY"�ӻ�", GRN"����", BLU"��", MAG"ź��ɫ"
, MAG"��", YEL"���", WHT"�ذ�", WHT"��", GRN"����", 
});
string *wo_material = ({
"��", "ϸɴ", "�Ż�", "�廨", "��", "����", "���", "����", "�Խ�", "�ƽ�", 
});   
string *wos_type = ({
"Ь"NOR, "ѥ"NOR, "��ѥ"NOR, "Ƥѥ"NOR,
});
string *mans_type = ({
"ѥ"NOR, "��ѥ"NOR, "��ѥ"NOR,"��ѥ"NOR,
});
string *wos_color = ({
RED"���", RED"����", HIY"�ӻ�", GRN"����", BLU"��", MAG"ź��ɫ"
, MAG"��", YEL"���", WHT"�ذ�", WHT"��", GRN"����", 
});
string *wos_material = ({
"��", "ϸɴ", "�Ż�", "�廨", "��", "����", "���", "����", "˿", "�ƽ�", 
}); 
string *mans_color = ({
CYN"��", BLU"��", WHT"��", HIB"����", GRN"����", HIR"糺�", 
BLK"��", WHT"�ذ�", HIM"��", MAG"ǳ��", 
});
string *mans_material = ({
"����", "��", "�ɻ�", "�ķ�", "ֱ��", 
});                                     
string comm_man_cloth()
{
    return man_color[ random ( sizeof ( man_color ) ) ] + com_material[ 
        random ( sizeof ( com_material ) ) ] + com_type[ random ( sizeof ( com_type ) ) ];
}
string high_man_cloth()
{
    return man_color[ random ( sizeof ( man_color ) ) ] + high_material[ random ( 
        sizeof ( high_material ) ) ] + high_type[ random ( sizeof ( high_type ) ) ];
}
string woman_cloth()
{
    return wo_color[ random ( sizeof ( wo_color ) ) ] + wo_material[ random ( sizeof ( 
        wo_material ) ) ] + wo_type[ random ( sizeof ( wo_type ) ) ];
}
string woman_shoes()
{
    return wos_color[ random ( sizeof ( wos_color ) ) ] + wos_material[ random ( sizeof ( 
        wos_material ) ) ] + wos_type[ random ( sizeof ( wos_type ) ) ];
}
string man_shoes()
{
    return mans_color[ random ( sizeof ( mans_color ) ) ] + mans_material[ random ( sizeof ( 
        mans_material ) ) ] + mans_type[ random ( sizeof ( mans_type ) ) ];
}



