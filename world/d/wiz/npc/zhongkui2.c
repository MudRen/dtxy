// zhongkui.c
// by fjz

#include <ansi.h>

inherit NPC;

#include "dirtyword.h"

void punish(object);

void create()
{
        set_name("��ظ", ({"zhong kui", "zhongkui"}));
        set("gender", "����" );
        set("age", 30);
        set("per", 5);//no rongmao description.

        set("long", "���˲�֪��ץ����ɣ���������׼�������ʲô���¡�\n");
        set("class", "taoist");
        set("combat_exp", 3000000);
        set("attitude", "peaceful");
        set_skill("unarmed", 250);
        set_skill("dodge", 250);
        set_skill("parry", 250);
        set_skill("blade", 250);
        set_skill("force", 250);   
        set_skill("literate", 280);
        set_skill("spells", 250);
        set("max_kee", 1500);
        set("max_sen", 1400);
        set("force", 4000);
        set("max_force", 2400);
        set("mana", 6000);
        set("max_mana", 3000);   
        set("force_factor", 120);
        set("mana_factor", 150);
        setup();
        if( clonep() ) CHANNEL_D->register_relay_channel("rumor");
        if( clonep() ) CHANNEL_D->register_relay_channel("chat");
        if( clonep() ) CHANNEL_D->register_relay_channel("wiz");
        if( clonep() ) CHANNEL_D->register_relay_channel("xyj");
        if( clonep() ) CHANNEL_D->register_relay_channel("sldh");
        if( clonep() ) CHANNEL_D->register_relay_channel("party");
        if( clonep() ) CHANNEL_D->register_relay_channel("ymdh");
        if( clonep() ) CHANNEL_D->register_relay_channel("es");
}

void relay_channel(object ob, string channel, string msg)
{

        int i;
        if( !userp(ob) || (channel == "sys") ) return;

        for(i=0; i<sizeof(msg_d); i++)
        {
            if( strsrch(msg, msg_d[i]) >= 0)
                   {
                    call_out("punish",1,ob);
                    return;
                    }
        }
}

void punish(object ob)
{
        command_function("chat* ������ظһ��ŭ�ȣ�"+ob->query("name")+" ���������ܲ����ˡ�");
        message_vision(HIC"\n���з���һ�����ӣ�һ�¾���ס$N�Ĳ��ӡ�\n"NOR+CYN"$N�쳤��ͷ�����Ű��۵ر������ˡ�\n"NOR, ob);
        ob->move("/d/wiz/blackroom");
        message_vision(CYN"��ظ�����㵨�Ӳ�С�������ˣ���ʵ�������\n"NOR, ob);
        message_vision(CYN"˵�ţ�����һ�ɣ�$N�����ڵ��ϡ�\n"NOR, ob);
}
