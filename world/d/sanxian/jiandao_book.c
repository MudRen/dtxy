// jiandao_book������ƪ
// writted by mind

#include <ansi.h>
inherit ITEM;



void create()
{
        set_name("������ƪ",({"jiandao yipian","yipian","book"}));
        set("unit","��");
        set("long","һ������š���������ɽ���ӹ������������Ĳ�ȱ��ࡣ\n");
        set("no_give",1);
        setup();
}
void init()
{
        add_action("do_study","study");
        add_action("do_study","du");
}
int do_study(string arg)
{
        int k;
        object me;
        string str;
        
        me=this_player();
        if( !living(me))        return 0;
        if (!id(arg))
        return 0;
        if(me->query_skill("spysword",1)<50||!me->query_skill("spysword",1))
        {
        tell_object(me,"��ġ��̿ͽ�����������������û�����򡸽������ء�\n");
        return 1;
        }
        k=me->query("old_flag/jiandao");
        if(!k||k==0)    k=3;
        if(k==10)       
        {
        tell_object(me,"����˲��Ƶ�����ϣ�������ġ��������Ѵﵽ��߾����ˣ����о���Ҳû������\n");
                return 1;
        }
        message_vision("$N����ϸ���Ķ���ר�С��������ľ���Ҫּ��\n",me);
        if((me->query_skill("literate",1)/2)<50+(k-2)*5)
        {
        tell_object(me,"���㵱ǰ��������������������ġ���������\n");
                return 1;
        }
        if(random(me->query_kar())<25)
        {
        tell_object(me,"�����ԡ�������������⣬���ֲ��ҿ϶���\n");
                return 1;
        }
        tell_object(me,HIW"��ԡ�������������Ѿ������"+chinese_number(k)+"�㾳�磡\n"NOR);
        str=me->name()+"�ԡ�������������Ѿ������"+chinese_number(k)+"�㾳�磡";
        message("channel:rumor",HIM"������ҥ����ĳ�ˣ�"+str+"\n"NOR,users());
        k=k+1;
         me->set("old_flag/jiandao",k);
        return 1;
}

