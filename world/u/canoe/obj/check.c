#include <ansi.h>
inherit ITEM;
int do_sign(string);
void init()
{
   add_action("do_sign","qianming");
}
void create()
{
        set_name(HIY"ǧ���ƽ�֧Ʊ"NOR, ({"check","jiangpin"}));
        set_weight(0);
        set("unit","��");
        set("long","����wizΪ�����������������������(�����qianmingһ������)");
    set("value",0);
        set("drug_type",",֧Ʊ");
setup();
}
int do_sign(string arg)
{
        object me = this_player();
    if (!id(arg)) return notify_fail("��Ҫ��ʲô��ǩ����\n");
         me->add("balance",10000000);  
    message_vision(HIC"\n  $N�ӻ����ͳ�һ�����õ�ë��,��֧Ʊ�տ��������һ��,\n"
"ֻ���������ɷ���Ĵ���ԾȻֽ��.\n\n"
  "  ��Ȼһ����������ļһ������$N��ǰ,��$N���нӹ�֧Ʊ,����ľ���һ��,˵��:\n"
"֧Ʊ��ǩ��,"HIY"һǧ���ƽ�"+HIC"��ת����Ǯׯ�˻�,��л�Ա�վ��֧��,���ٽ�����!!\n\n"NOR,me);
            destruct(this_object());
return 1;
}

