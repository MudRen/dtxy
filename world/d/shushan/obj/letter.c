#include <ansi.h> 

inherit ITEM;

void create()
{
        set_name(HIW"��"NOR, ({"letter", "xin"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
"����������Ͻ�˿��֯����ֽ����������ң�ִټ�д�µļ����֣�\n"
"\n"

"         �Գ����У����ɷ�Ҳ������֮�ѣ�����ǧ������֮\n" 
"     �������Ҳ��������Ѿȳ�����ң�������У��������\n" 
"     ���ƿ̲��ݻ�������������ɽ���һ�ţ��������\n" 
"     �����յأ�������������������������������������������\n"
"\n"
"                                             ��ң����\n");
                set("material", "paper");
        }
  setup();
}
