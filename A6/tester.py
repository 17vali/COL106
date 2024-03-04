import random as r

counts = {}
separators = separators = ".,-:!\"'()?[];@"
sentences = []
metadata = []
patterns = []

num_tc_dict = 50000
num_tc_search = 50

FILE_NAMES = "files_gandhi49.txt"
TC_DICT = "testcase_dict.txt"
ANS_DICT = "ans_dict.txt"
TC_SEARCH = "testcase_search.txt"
DUMP_FILE = "dictionary_dump_ans.txt"
PROB_DENOM = 10000 #0.5 * num lines / num tc

with open(FILE_NAMES) as F:
    files = F.readlines()

vers = input("Tester for part 1 or 2?")
if vers.strip() == "2":
    i = 0
    for filename in files:
        try:
            with open(filename.strip()) as F:
                lines = F.readlines()
            i = i + 1
            for j in range(len(lines)):
                s = lines[j]
                rc = s.find(")")
                tup = eval(s[:rc+1])
                s = s[rc+1:].strip()
                sentences.append(s)
                metadata.append(tup)
                todo = r.randint(1, PROB_DENOM)
                if (todo == 1):
                    third = r.randint(1, 10)
                    if (third < 6):
                        tmp_len = r.randint(1, len(s) // 3)
                    elif (third < 10):
                        tmp_len = r.randint(len(s) // 3 + 1, 2*len(s) // 3)
                    else: 
                        tmp_len = r.randint(2*len(s) // 3 + 1, len(s))
                    idx = r.randrange(0, len(s) - tmp_len + 1)
                    patterns.append(s[idx:idx+tmp_len])
            print("File", i , "of", len(files), "processed")
        except FileNotFoundError:
            print("File with name " + filename + " not found!")
        except:
            print("Error reading file " + filename)

    print("Generating testcases...")
    file_tc = []
    file_ans = []
    ac = 0
    i = 0

    while (i < num_tc_search) and (ac < len(patterns)):
        i += 1
        print("Testcase", i, "generated")
        todo = r.randint(1, 5)
        if (todo == 1):
            file_tc.append(".cbi3923^#*^&rfgv\n")
            # file_ans.append("0\n")
            continue
        # inf = []
        # for j in range(len(sentences)):
        #     start = 0
        #     while True:
        #         start = sentences[j].find(patterns[i], start)
        #         if start == -1: break
        #         inf.append(tuple((metadata[j][0].strip("'"), metadata[j][1], metadata[j][2], metadata[j][3], start)))
        #         start += 1
        
        # to_append = ""
        # to_append += str(len(inf)) + " "
        # for j in range(len(inf)):
        #     to_append += str(inf[j][0]) + " " + str(inf[j][1]) + " " + str(inf[j][2]) + " " + str(inf[j][3]) + " " + str(inf[j][4]) + " " 
        # file_ans.append(to_append + "\n")
        file_tc.append(patterns[ac] + "\n")
        ac += 1

    with open(TC_SEARCH, "w") as F:
        F.writelines(file_tc)
    
    # with open(TC_ANS, "w") as F:
    #     F.writelines(file_ans)
    
else:
    ques = input("Generate word counts? (Y/N): ")

    if ques.lower() == "y":
        i = 0
        for filename in files:
            try:
                with open(filename.strip()) as F:
                    lines = F.readlines()
                i = i + 1
                for j in range(len(lines)):
                    s = lines[j]
                    rc = s.find(")")
                    tup = eval(s[:rc+1])
                    s = s[rc+1:]
                    for sep in separators:
                        s = s.replace(sep, " ")
                    words = s.split()
                    for word in words:
                        word_real = word.lower()
                        counts[word_real] = counts.get(word_real, 0) + 1
                print("File", i , "of", len(files), "processed")
            except FileNotFoundError:
                print("File with name " + filename + " not found!")
            except:
                print("Error reading file " + filename)

        word_counts = []
        for word in sorted(counts.keys()):
            word_counts.append(word + ", " + str(counts[word]) + "\n")

        with open(DUMP_FILE, "w") as F:
            F.writelines(word_counts)

    else:
        try:
            with open(DUMP_FILE, "r") as F:
                word_counts = F.readlines()
            for i in range(len(word_counts)):
                string = word_counts[i].strip().split(", ")
                counts[string[0]] = int(string[1])
        except:
            print("Word counts file(" + DUMP_FILE + ") invalid!")

    print("Generating testcases...")
    file_tc = []
    file_ans = []

    for i in range(num_tc_dict):
        wd = r.choice(list(counts.keys()))
        file_tc.append(wd + "\n")
        file_ans.append(str(counts[wd]) + "\n")
        print("Testcase", i+1, "generated")

    with open(TC_DICT, "w") as F:
        F.writelines(file_tc)

    with open(ANS_DICT, "w") as F:
        F.writelines(file_ans)