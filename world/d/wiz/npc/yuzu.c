// zhongkui.c
// by fjz

#include <ansi.h>

inherit NPC;

string *msg_d = ({
                      "�����","�����","ɵB","�Ҳ�","����","������˯","�л��û��","û���᣿",
                      "�٣�","��!","fuck","FUCK","Fuck","���","��û�л��","����?","shit","SHIT","Shit",
                      "fUck","FUcK","FUCk","FuCk","�����","SHit","sHit","SHIt","ShiT",
                      "�����̵�","����������","�����","��үү��","��û�д�����","cao","CAO","Cao",
                      "�������ƨ","������","������","������","û���أ�","������","�ϵ�","����",
                      "������","�����","��ƨwiz","��wiz","��wiz","��wiz","������",
                      "������","�����","������","�ƣգã�","F u c k","f u c k","����","����","���",
                      "����","��!","�ҿ�","��ƨ","��ʺ","������","����","6mang","���","С��","caobi",
                      "����","��",});
                      

void punish(object);

int give_quest();

void create()
{
        set_name("��ɽ����", ({"heishan laoyao", "laoyao", "yao"}));
        set("title", WHT"����������Ѳ��ʹ��"NOR);
        set("gender", "����" );
        set("age", 30);
        set("per", 12);//no rongmao description.

        set("long", "һ�����ص����䣬��������׼�������ʲô���¡�\n");
        set("class", "taoist");
        set("combat_exp", 3000000);
        set("attitude", "peaceful");
        set_skill("unarmed", 350);
        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_skill("blade", 350);
        set_skill("force", 350);   
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
        set("inquiry", ([
//		"ץ��"	:	(: give_quest :),
	]));        
        setup();
        if( clonep() ) CHANNEL_D->register_relay_channel("rumor");
        if( clonep() ) CHANNEL_D->register_relay_channel("chat");
        if( clonep() ) CHANNEL_D->register_relay_channel("sldh");
        if( clonep() ) CHANNEL_D->register_relay_channel("party");
        if( clonep() ) CHANNEL_D->register_relay_channel("bd");
        if( clonep() ) CHANNEL_D->register_relay_channel("es");
        if( clonep() ) CHANNEL_D->register_relay_channel("xyj");
		if( clonep() ) CHANNEL_D->register_relay_channel("mp");
        carry_object("/d/lingtai/obj/xiangpao")->wear();

}

void relay_channel(object ob, string channel, string msg)
{

        int i;
        if( !userp(ob) || (channel == "sys") ) return;

        for(i=0; i<sizeof(msg_d); i++)
        {
        	msg=replace_string(msg, " ", "");
        	msg=replace_string(msg, "��", "");
            if( strsrch(msg, msg_d[i]) >= 0)
                   {
                    call_out("punish",1,ob);
                    return;
                    }
        }
}


void punish(object ob)
{
    	int i;
      if(ob->is_fighting()||ob->is_busy())
    {
    call_out("punish", 1, ob); return; }
        command_function("chat* ������ɽ����һ��ŭ�ȣ�"+ob->query("name")+" ���������ܲ����ˡ�");
        message_vision(HIR"���з���һ�����ӣ�һ�¾���ס$N�Ĳ��ӡ�\n"NOR+CYN"$N�쳤��ͷ�����Ű��۵ر������ˡ�\n"NOR, ob);
        
		ob->move("/d/wiz/qiushi");
		        message_vision(HIW"��ɽ������$N���������ҿڳ����Ի���ڴ˵�����ʵʵ���Ҷ��š�\n", ob);
        message_vision(HIW"˵�ţ�����һ�ɣ�$N�����ڵ��ϡ�\n"NOR, ob);
        command("fool");
        command("say ��ץ��һ����");
}
/*
int give_quest()
{
	object who, seal;
	mapping room;
	
	who=this_player();
	if((time()-who->query("catch_ghost/last_time"))<300)
	{
		command("say ���ڻ���Ƚ�̫ƽ������ȥЪ�˰ɡ�");
		return 1;
	}
	seal=new("/d/city/obj/seal");
	seal->set("master", who);
      do{ room=LOCATION_D->random_location(); } while(!strlen(room["long"]));
	seal->set("file_name", room["file"]);
	seal->set("desc", room["long"]);
	seal->move(who);
	who->set("catch_ghost/last_time", time());
	command("nod");
	message_vision("$N��$n˵�������ŷ����㣬�㿴������д�ķ���ȥץ��ɡ�\n", 
	this_object(), who);
	return 1;
}

int accept_object(object who, object ob)
{
	int reward, times;
	string msg;
	
	if(!ob->query("finished")||
		who!=ob->query("master"))
		return 0;
	command("nod");
	message_vision("$N��$n˵�����ܺã�\n", this_object(), who);
	times=who->query_temp("catch_ghost");
	reward=800+random(200)*times+200*times;
	msg="��������";
	switch(random(3))
	{
		case 0:
			who->add("wuxue_exp", reward);
			who->add("catch_ghost/cache/wuxue", reward);
			msg+=chinese_number(reward)+"����ѧ��\n";
			break;
		case 1:
			who->add("combat_exp", reward);
			who->add("catch_ghost/cache/dx", reward);
			msg+=COMBAT_D->chinese_daoxing(reward)+"���С�\n";
			break;
		default:
			who->add("potential", reward/4);
			who->add("catch_ghost/cache/pot", reward/4);
			msg+=chinese_number(reward/4)+"��Ǳ�ܡ�\n";
	}
	who->add_temp("catch_ghost", 1);
	if(who->query_temp("catch_ghost")>9)
		who->set_temp("catch_ghost", 0);
        MONITOR_D->report_system_object_msg(who, "[ץ��]"+msg);
        tell_object(who, "��"+msg);
        return 1;
}
*/

