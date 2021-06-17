//quest.h

inherit F_LOCATION;
#define OUT_TIME 30
#define ALLOW_TIME 1*60

int give_quest()
{
	string type;
	object player;
	mapping question;
	
	player=this_player();
	type=query("quest_type");
	if(time()-player->query("g_quest/"+type+"/time")<ALLOW_TIME)
	{
		if(player->query("g_quest/"+type+"/quest"))
		{
			command("angry");
			command("say ��һ�ε����������û�а��׵��ɣ�\n");
			return 1;
		}
		command("sorry");
		command("say ���ڲ�û��ʲô������������������һ�������ɡ�\n");
		return 1;
	}
	player->set("g_quest/"+type+"/time", time());
	question=ROBOT_D->give_question();
	printf("%s˵��������������ͷ�������ȿ����㡣\n", name(1));
	printf("%s", question["quest"]);
	printf("����%s���ڻش�\n", chinese_number(OUT_TIME));
	input_to("get_answer", player, question, type);
	return 1;
}

int give_mission(object player, string type)
{
	object target, goods;
	string place, desc, goods_type;
	mapping room;
	
	switch(type)
	{
		case "captor":
		goods_type="mihan";
		break;
		case "dancer":
		goods_type="yaoqin";
		break;
//		case "knight":
//		goods_type="mihan";
//		break;
		default:
		return 0;
		break;
	}
	player->set("g_quest/"+type+"/quest", 1);
//	place=random_location();
	room=LOCATIOND->random_location();
	place=room["file"];
	desc=room["area"];
	sscanf(place, "[%s]%s", desc, place);
	target=new(__DIR__"target/"+type);
	target->set("master", player);
	target->set("type", type);
	goods=new(__DIR__"obj/"+goods_type);
	goods->set("master", player);
	goods->set("target", target);
	target->move(place);
	goods->move(player);
	tell_object(player, 
		sprintf("%s����Ķ�������˵���������%s�͵�%s(%s)���С�\n"
			+"���һ��%s������%s����ȥ�ٻأ�\n",
			name(1), goods->name(1), target->name(1),
			capitalize(target->query("id")), target->name(1), desc));
	message_vision(sprintf("$N��$nһ%s%s��\n",
			goods->query("unit"), goods->name(1)),
			 this_object(), player);
	return 1;
	
}
void get_answer(string arg, object who, mapping quest, string type)
{
	int answer;
	
	if(!arg||sscanf(arg, "%d", answer)!=1)
	{
		printf("��ֻ�ܻش�һ�����֣�\n");
		input_to("get_answer", who, quest, type);
		return;
	}
	if(answer!=quest["answer"])
	{
		command("sigh");
		printf("%s˵�������ⶼ�ش��ˣ���������Ҹ�������񰡣�\n",
			name(1));
		return;
	}
	if(time()-who->query("g_quest/"+type+"/time")>OUT_TIME)
	{
		command("sigh");
		printf("%s˵����Ҫ��ô�ò��ܻش𣬻�������Ҹ�������񰡣�\n",
			name(1));
		return;
	}
	command("nod");
	give_mission(who, type);
	return;
}