// by gslxz@mhsj 1/7/2001
#include <ansi.h>
inherit F_CLEAN_UP;
int main(object me, string arg)
{
        object ob;
        string banghui;
        object lingpai;
        mapping player;
        if( (banghui=me->query("banghui")))
                return notify_fail("��Ǹ�����Ѿ��ǰ�ᡸ"+me->query("banghui")+"�������ˣ��޷�����������ᡣ\n");
        if(me->is_fighting()||me->is_busy())
                return notify_fail("����æ���ء�\n");
        if(! arg)
                return notify_fail("��Ҫ����˭�İ�᣿\n");
        if( me->query("id")==arg)
                return notify_fail("��û����ô����\n");
        if(! objectp(ob=present(arg,environment(me))))
                return notify_fail("���û����ô���ˡ�\n");
        if((object)me->query_temp("oldsix/target")!=ob)
                return notify_fail("��Ǹ��"+ob->query("name")+"��û��������μ����İ�ᡣ\n");
        if(! (banghui=ob->query("banghui")))
                return notify_fail("��Ǹ��"+ob->query("name")+"���ڲ������κΰ�ᣡ\n");
      if (this_player()->query("combat_exp") < 1000 )
                return notify_fail("��ų��뽭������ĥ��ĥ����.\n");
        lingpai=new("/obj/lingpai");
        lingpai->create(banghui);
        if( ! lingpai->query("no_use")) {
        player=lingpai->query("player");
        if(! mapp(player))      player=([]);
        player[me->query("id")]=me->query("id");
        lingpai->set("player",player);
        lingpai->save();
        me->set("banghui",ob->query("banghui"));
        me->set("have_banghui",(int)me->query("have_banghui")+1);
        me->delete_temp("oldsix/target");
        me->save();
        me->set("title",HIG+ob->query("banghui")+"����"NOR);
// by gslxz@mhsj 1/7/2001
          destruct(lingpai);
                message("channel:rumor", 
   YEL"�����������"+me->query("name")+"�����ᡸ"HIW+ob->query("banghui")+NOR+YEL"����\n"NOR,users());
        return 1;
        }
        else    {
        destruct(lingpai);
        return notify_fail("�Է�����ļ������⣬������ʦ��ϵ��\n");
        }
}
int help(object me)
{
        write(@HELP
ָ���ʽ��jiaru <ĳ��>
���ָ����������ĳ�˵İ�ᡣ
ǰ����ĳ�˱��������㡣
HELP
        );
        return 1;
}

