import re

print("Loading mojang->obf mappings...")
mojang_to_obf_class = {}
mojang_to_obf_method = {}
mojang_to_obf_field = {}

current_class_mojang = ""
current_class_obf = ""

with open("client.txt", "r") as f:
    for line in f:
        if line.startswith("#"): continue
        line = line.strip()
        if not line: continue
        
        if not line.startswith(" ") and " -> " in line:
            parts = line.split(" -> ")
            current_class_mojang = parts[0].replace(".", "/")
            current_class_obf = parts[1][:-1]
            mojang_to_obf_class[current_class_mojang] = current_class_obf
        elif line.startswith(" ") and " -> " in line:
            line = line.strip()
            parts = line.split(" -> ")
            if ":" in parts[0]:
                method_part = parts[0].split(":")[-1].strip()
                method_name = method_part.split("(")[0].split(" ")[-1]
                obf_name = parts[1]
                mojang_to_obf_method[current_class_mojang + "." + method_name] = obf_name
            else:
                field_part = parts[0].split(" ")
                field_name = field_part[1]
                obf_name = parts[1]
                mojang_to_obf_field[current_class_mojang + "." + field_name] = obf_name

print("Loading obf->inter mappings...")
obf_to_inter_class = {}
obf_to_inter_method = {}
obf_to_inter_field = {}

with open("mappings_1.21.tiny", "r") as f:
    for line in f:
        parts = line.strip().split("\t")
        if parts[0] == "CLASS":
            obf_to_inter_class[parts[1]] = parts[2]
        elif parts[0] == "METHOD":
            # METHOD <obf_class> <desc> <obf> <intermediary>
            obf_class = parts[1]
            obf_method = parts[3]
            obf_to_inter_method[obf_class + "." + obf_method] = parts[4]
        elif parts[0] == "FIELD":
            obf_class = parts[1]
            obf_field = parts[3]
            obf_to_inter_field[obf_class + "." + obf_field] = parts[4]

print("Updating mappings.h...")
with open("src/config/mappings.h", "r") as f:
    content = f.read()

# Replace Classes
class_matches = re.finditer(r'inline constexpr const char\* (\w+_Class)\s*=\s*"([^"]+)";', content)
for m in class_matches:
    var_name = m.group(1)
    mojang_name = m.group(2)
    
    # Exceptions (libraries)
    if "java/" in mojang_name or "joml" in mojang_name or "authlib" in mojang_name:
        continue
        
    if mojang_name in mojang_to_obf_class:
        obf = mojang_to_obf_class[mojang_name]
        inter = obf_to_inter_class.get(obf, mojang_name)
        content = content.replace(f'"{mojang_name}"', f'"{inter}"')

# For methods, the format in mappings.h is:
# inline constexpr const char* MC_getInstance = "getInstance";
# We need to map this based on context.
# Since it's hard to parse context accurately, I'll write out the specific Intermediary mappings directly.
