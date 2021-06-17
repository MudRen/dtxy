inherit NPC;
#include <ansi.h>
#include <obstacle.h>
#define LIMIT_LENGTH    40 // ����
string replace_long(string long);
void random_place(object who,object seal);
mapping *wheres=({
      (["chinese":                "������",
       "weizhi" :              "/d/qujing/jisaiguo",]), 
 (["chinese":                "��������",
        "weizhi" :              "/d/changan",]), 
  (["chinese":                "�����Ƕ�",
       "weizhi" :              "/d/eastway",]), 
  (["chinese":                "����ׯ",
       "weizhi" :              "/d/gao",]), 
  (["chinese":                "�����",
       "weizhi" :              "/d/kaifeng",]), 
  (["chinese":                "����ɽ",
       "weizhi" :              "/d/lingtai",]), 
  (["chinese":                "�¹�",
       "weizhi" :              "/d/moon",]), 
  (["chinese":                "����ɽ",
       "weizhi" :              "/d/nanhai",]), 
  (["chinese":                "����",
       "weizhi" :              "/d/sea",]), 
  (["chinese":                "��������",
       "weizhi" :              "/d/westway",]), 
  (["chinese":                "��ׯ��",
       "weizhi" :              "/d/qujing/wuzhuang",]), 
  (["chinese":                "��¥һ��",
       "weizhi" :              "/d/ourhome/honglou",]), 
  (["chinese":                "�ظ�",
       "weizhi" :              "/d/death",]), 
  (["chinese":                "�����ɵ�",
       "weizhi" :              "/d/penglai",]), 
  (["chinese":                "��ѩɽ",
       "weizhi" :              "/d/xueshan",]), 
  (["chinese":                "��ͷɽ",
       "weizhi" :              "/d/qujing/baotou",]), 
      (["chinese":                "�ڼ���",
       "weizhi" :              "/d/qujing/wuji",]), 
      (["chinese":                "���ٹ�",
       "weizhi" :              "/d/qujing/chechi",]), 
      (["chinese":                "�����",
       "weizhi" :              "/d/qujing/baoxiang",]), 
      (["chinese":                "�����",
       "weizhi" :              "/d/qujing/biqiu",]), 
      (["chinese":                "��������",
       "weizhi" :              "/d/city",]), 
      (["chinese":                "���ɿ�",
       "weizhi" :              "/d/qujing/fengxian",]), 
      (["chinese":                "��ƽ��",
       "weizhi" :              "/d/qujing/jinping",]), 
      (["chinese":                "Ů����",
       "weizhi" :              "/d/qujing/nuerguo",]), 
       (["chinese":                "�շ���",
       "weizhi" :              "/d/qujing/qinfa",]), 
       (["chinese":                "���ù�",
       "weizhi" :              "/d/qujing/tianzhu",]), 
       (["chinese":                "����",
       "weizhi" :              "/d/qujing/yuhua",]), 
       (["chinese":                "���ù�",
       "weizhi" :              "/d/qujing/tianzhu",]), 
       (["chinese":                "���Ϲ�",
       "weizhi" :              "/d/qujing/zhuzi",]), 
      });

      void create()
{
        set_name("��ظ", ({"zhong kui", "zhongkui", "kui"}));
        set("title", WHT"�����"NOR);
        set("gender", "����" );
        set("age", 30);
    set("per", 100);
 set("long", "��������������ܵ�ץ����ɣ�����������Խ���(xiangyao)��\n");

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
                carry_object("/d/lingtai/obj/xiangpao")->wear();

}
void init()
{
    add_action("do_quest", "xiangyao");
    add_action("do_cancel", "cancel");
}
int do_quest()
{
	object who, seal;
	mapping room;
	int level,i;
	string kind,where;
	
	who=this_player();
	message_vision("$N���ĳ���ض�$n˵��������Ը��ǰȥ������ħ����\n",who,this_object());
	if (who->query("obstacle/number") < sizeof(obstacles) && !wizardp(who))
             {message_vision(CYN"\n$N˵����$n��δȡ���澭���ó�����������ܽ�ħ���֡�\n"NOR,this_object(),who);
              return 1;
             }
        if( who->query("canoetask/get") )
             {message_vision(CYN"\n$N˵�����Ҳ����Ѿ����������$n�𣬿����̡�\n"NOR,this_object(),who);
              return 1;
             }
        
        if( who->query("canoetask/fail") )
             {message_vision(CYN"\n$N˵����$n�ȵ����������������������У�����������ɡ�\n"NOR,this_object(),who);
              return 1;
             }
        
        if( who->query("canoetask/accomplish") )
             {message_vision(CYN"\n$N˵����������ħ��Ȼ��Ҫ��Ҳǧ��Ҫ������������У�����
�����׻����������ħ���ģ������ȥ�����úò���ղŵ�ս��ȥ�ɡ�\n"NOR,who);
              return 1;
             }
             
	if((time()-who->query("canoetask/last_time"))<3)
	{
		command("say ���ڻ���Ƚ�̫ƽ������ȥЪ�˰ɡ�");
		return 1;
	}
	seal=new(__DIR__"obj/seal");
	seal->set("master", who);
        random_place(who,seal);
       
        //ȷ������ȼ�
        level = random(10);
        if (level<4) level=1;
        else if (level<7) level=2;
        else if (level<9) level=3;
        else level=4;
        
        //ȷ����������
        i = random(5);
        if (i==0) kind="ɱ";
        else if (i==1) kind="��";
        else if (i==2) kind="��";
        else if (i==3) kind="��";
        else kind="Ȱ";
        
        who->set("canoetask/get",1);
        who->set("canoetask/level",level);
        who->set("canoetask/kind",kind);
        where=seal->query("where"); 
        seal->set("level",level);
        seal->set("kind",kind);
        seal->set("times",random(5)+3);
        switch (kind)
          {
          	case "ɱ":
          	 {
          	 message_vision(CYN"\n$N˵���������и�������"+where+"������û���˹�
�Ѿ���ɱ�˲����޹��������ӯ�ˣ������ȥ����������\n"NOR,this_object(),who);
		 break;
		 }
          	case "��":
          	 {
          	 message_vision(CYN"\n$N˵���������и�������"+where+"������û���˹�
��δ�����ӯ�������ȥ�������ܻ������������Ե㻯����\n"NOR,this_object(),who);
		 break;
		 }
          	case "��":
          	{
          	message_vision(CYN"\n$N˵���������и�������"+where+"������û���˹�
�ոյ�����ɽȴ���¶��ݣ���ȥ�ݺݽ�ѵ��fight����һ�ء�\n"NOR,this_object(),who);
 		break;
 		}
		case "Ȱ":
		{
		message_vision(CYN"\n$N˵���������и�������"+where+"������û���˹�
���Բ�����ֻ��δ�ܳ����Խ������ȥ�㻯��persuade������\n"NOR,this_object(),who);
        	break;
        	}
                case "��":
		{
		message_vision(CYN"\n$N˵���������и�������"+where+"������û���˹�
�������ʷǷ����Ǹ�����֮�ģ���ȥ�����շ���shoufu���ɡ�\n����Ͻ������������������ã�����š�"NOR,this_object(),who);
new(__DIR__"obj/zijinhu")->move(who);
          	}
        }
        message_vision(CYN"\n���ţ�$N��$nһ�ŷ���˵�����������ŷ�������а�����\n"NOR,this_object(),who);
      //  who->set("canoetask/where",where);
        who->set("canoetask/start_time",time());
        MONITOR_D->report_system_msg (who->name()+"�ӵ�һ���Ѷ�"+chinese_number(level)+"��"+kind+"������");
      return 1;
}
int accept_object(object who, object ob)
{
       if(!ob->query("canoetask"))
           return 0;
       if(who->query("canoetask/kind") != "��"||!who->query_temp("canoetask/shoufu"))
           return 0;
       who->start_busy(2);
       who->set("canoetask/accomplish",1);
       who->delete_temp("canoetask/shoufu");
       if(random(2)) message_vision(CYN"$N���������$n��ͷ˵�����ú��ӣ����������ʮ���һ�������ң���\n", this_object(),who);
       else message_vision(CYN"$N����������$n�ı�˵�����ú��ӣ����ò�������ȥ��������ɡ�\n", this_object(),who);   
       return 1;
}

void random_place(object who,object seal)
{
        int  fs,k;
        mixed*  file;
        object newob;
        string dirs;
        k=random(sizeof(wheres));
        dirs=wheres[k]["weizhi"];
        seal->set("where",wheres[k]["chinese"]);
        file = get_dir( dirs+"/*.c", -1 );
        if( !sizeof(file) )  return;
        for(k=0;k<5;k++)
         {
           fs = random(sizeof(file));
           if( file[fs][1] > 0 )
             {
              dirs+="/"+file[fs][0];
              newob=load_object(dirs);
                 if (newob)
                  {  
                   seal->set("file_name", dirs);
	           seal->set("desc",replace_long(newob->query("long")) );
	           seal->move(who);
	           who->set("canoetask/last_time", time()); 
        	  }
	     }
	}
}
string replace_long(string long)
{
	string tmp="", target="";
	int length, start, i;
	int blank_flag=0;
	
	long=replace_string(long, "\n", "");
	for(i=0;i<strlen(long);i++)
		if(long[i]>160 && long[i]<255)
		 	tmp+=long[i..i];
	length=strlen(tmp);
	if(length<LIMIT_LENGTH*2)
		return tmp;
	start=random(length-LIMIT_LENGTH);
	if(start%2)
		start--;
	length=0;
	for(i=start;i<start+LIMIT_LENGTH;i+=2)
	{
		if(blank_flag<-random(2)-2)
		{
			target+="��";
			length++;
			if(random(2) || length>2)
			{
				blank_flag=0;
				length=0;
			}
		}
		else
		{
			blank_flag--;
			target+=tmp[i..i+1];
		}
	}
	return target;
}
int do_cancel()
{
	object who = this_player();
	
	if (!who->query("canoetask/get"))
	     {tell_object(who,"��û����������\n"); return 1;}
	if(present("ghost seal",who)) destruct(present("ghost seal", who));   
	who->command("say ���������ӿ�������Ϊ����");
	message_vision(CYN"\n$N˵�����ðɣ������ջ�ȥ�ˣ��㵽�����úò���ȥ�ɡ�\n"NOR,this_object(),who);
	who->set("canoetask/fail",1);
	who->delete("canoetask/get");
	return 1;
}	

