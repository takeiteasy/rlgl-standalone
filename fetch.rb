require 'net/http'

def get(uri)
    resp = Net::HTTP.get_response(uri)
    abort "ERROR: #{resp.code}" unless resp.is_a? Net::HTTPSuccess
    resp.body.split("\n")
end

rlgl_src = get(URI('https://raw.githubusercontent.com/raysan5/raylib/master/src/rlgl.h'))
rlgl_hdr_end = -1
rlgl_impl_start = -1
rlgl_impl_end = -1

rlgl_src.each_with_index do |line, i|
  case line
  when /^#endif \/\/ RLGL_H$/
    rlgl_hdr_end = i
  when /^#if defined\(RLGL_IMPLEMENTATION\)$/
    rlgl_impl_start = i+1
  when /^#endif  \/\/ RLGL_IMPLEMENTATION$/
    rlgl_impl_end = i-2
  end
end

rlgl_c = ["#include \"rlgl.h\""]
for i in rlgl_impl_start..rlgl_impl_end
  rlgl_c.append rlgl_src[i]
end
rlgl_h = []
for i in 0..rlgl_hdr_end
  rlgl_h.append rlgl_src[i]
end

rmath_src = get(URI('https://raw.githubusercontent.com/raysan5/raylib/master/src/raymath.h'))
rmath_hdr_start = -1
rmath_hdr_end = -1
rmath_impl_start = -1

rmath_src.each_with_index do |line, i|
    case line
    when /^\/\/ Defines and Macros/
        rmath_hdr_start = i-1
    when /^#include <math\.h>/
        rmath_hdr_end = i-1
        rmath_impl_start = i+1
    end
end

rmath_c = ["#include \"raymath.h\""]
for i in rmath_impl_start..rmath_src.length-2
    rmath_c.append rmath_src[i]
end

File.write 'src/rlgl.c', rlgl_c.join("\n")
File.write 'src/rlgl.h', rlgl_h.join("\n")
File.write 'src/raymath.c', rmath_c.join("\n")

rmath_h = ["#ifndef RAYMATH_H", "#define RAYMATH_H", "", "#ifndef RMAPI", "#define RMAPI", "#endif", "", "#include <math.h>", ""]
for i in rmath_hdr_start..rmath_hdr_end
    rmath_h.append rmath_src[i]
end
rmath_h.push *["#if defined(__cplusplus)", "extern \"C\" {", "#endif"]
for line in `ctags -x --c-kinds=+p -u src/raymath.c`.split("\n")
    /^(?<name>\S+)\s*(?<type>\S+)\s*(?<line>\d+)\s*(?<file>\S+)\s(?<defn>[^\n]+)/ =~ line
    rmath_h.append defn.strip + ";"
end
rmath_h.push *["#if defined(__cplusplus)", "}", "#endif"]
rmath_h.append "#endif // RAYMATH_H"

File.write 'src/raymath.h', rmath_h.join("\n")
