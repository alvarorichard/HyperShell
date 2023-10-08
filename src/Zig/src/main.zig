const std = @import("std");
const stdout = std.io.getStdOut().writer();
const Allocator = std.mem.Allocator;
const mem = std.mem;

const c = @cImport({
    @cInclude("unistd.h");
    @cInclude("sys/types.h");
    @cInclude("sys/wait.h");
});

const HS_RL_BUFSIZE :usize = 1024;
const HS_TOK_BUFSIZE : usize = 64;
const HS_TOK_DELIM: []const u8 = " \t\r\n" ++ [_]u8{7};

fn hs_loop(allocator: *Allocator) !void {
    var status: c.int = 1; // Initialize to a non-zero value to enter the loop
    while (status != 0) {
        try std.debug.print(">> ", .{});
        const line = try std.io.readLineAlloc(allocator, 1024); // Read line with allocation
        defer allocator.free(line); // Free the memory when done

        const args = try hs_split_line(allocator, line); // Assuming hs_split_line also allocates memory
        defer allocator.free(args); // Free the memory when done

        status = try hs_execute(args); // Assuming hs_execute returns c.int and can fail
    }
}


fn hs_split_line(allocator: *Allocator, line: []const u8) !?[]const []const u8 {
    _ = line;
    _ = allocator;

    
    

    return null;
}

fn hs_execute(args: []const []const u8) !c.int {
    _ = args;
    // Your implementation here
    return 0;
}



pub fn main() !void {
    const allocator = std.heap.page_allocator;
    try hs_loop(&allocator);
}